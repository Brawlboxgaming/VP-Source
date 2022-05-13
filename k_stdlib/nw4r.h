#ifndef __KAMEK_NW4R_H
#define __KAMEK_NW4R_H

#include "kamek.h"

#define NODE_TO_ITEM(node, type, field) \
    ((type *)((char *)node - offsetof(type, field)))
    
#define offsetof(st, m) \
    ((u32)&(((st *)0)->m))

namespace nw4r {
	namespace ut {
		struct Color {
			union {
				struct { u8 r,g,b,a; };
				u32 rgba;
			};
		};


		struct Link {
			void *prev, *next;
		};
		struct List {
			Link *head, *tail;
			u16 count, offset;
		};

		void List_Init(List *list, u16 offset);
		void List_Append(List *list, void *newObj);
		void List_Insert(List *list, void *insertBefore, void *newObj);
		void List_Remove(List *list, void *obj);
		void *List_GetNext(List *list, void *obj);
		void *List_GetPrev(List *list, void *obj);

		class LinkListNode {
		public:
			LinkListNode *next;
			LinkListNode *prev;
		};

		class LinkList {
		public:
			int count;
			LinkListNode initialNode;
		};

		// TODO: Character/text/font utility classes
		template <class T>
		class TagProcessorBase { };
	}


	namespace db {
		// prints message to NW4R console
		void Exception_Printf_(const char *, ...);
	}


	namespace math {
		namespace detail {
			f32 FExp(f32);
			f32 FLog(f32);
		}

		inline f32 FExp(f32 value) { return detail::FExp(value); }
		inline f32 FLog(f32 value) { return (value > 0.0f) ? detail::FLog(value) : NAN; }
		f32 FrSqrt(f32);

		// TODO: inline Idx (rather than FIdx) versions of Sin, Cos, SinCos
		f32 SinFIdx(f32 fidx);
		f32 CosFIdx(f32 fidx);
		void SinCosFIdx(f32 *pSin, f32 *pCos, f32 fidx);
		f32 Atan2FIdx(f32 y, f32 x);
		u16 Atan2Idx(f32 y, f32 x);


		struct VEC2 : public Vec2 { };
		struct VEC3 : public Vec {
			void Report(bool addNewLine, const char *prefixText = 0);
		};

		struct MTX33 { f32 data[3][3]; };
		struct MTX34 { f32 data[3][4]; };
		struct MTX44 { f32 data[4][4]; };

		void MTX33Identity(MTX33 *mtx);
		void MTX34ToMTX33(MTX33 *dest, const MTX34 *source);
		void MTX34Zero(MTX34 *mtx);
		void MTX34Add(MTX34 *dest, const MTX34 *sourceA, const MTX34 *sourceB);
		void MTX34Scale(MTX34 *dest, const MTX34 *sourceMatrix, const VEC3 *sourceVector);
		void MTX34Trans(MTX34 *dest, const MTX34 *sourceMatrix, const VEC3 *sourceVector);
		void MTX34RotAxisFIdx(MTX34 *dest, const VEC3 *vector, float fidx);
		void MTX34RotXYZFIdx(MTX34 *dest, float x, float y, float z);
		void VEC3TransformNormal(VEC3 *dest, const MTX34 *sourceMatrix, const VEC3 *sourceVector);
		void MTX44Identity(MTX44 *mtx);
		void MTX44Copy(MTX44 *dest, const MTX44 *source);
		
		struct PLANE {
			VEC3 vector;
			f32 constant;

			void Set(const VEC3 *a, const VEC3 *b, const VEC3 *c);
		};

		struct AABB {
			VEC3 minPoint, maxPoint;

			void Set(const VEC3 *pointArray, u32 pointCount);
			void Set(const AABB *otherAABB, const MTX34 *matrix);
		};

		struct FRUSTUM {
			MTX34 matrix;
			PLANE left, right, top, bottom;
			f32 near, far;
			AABB aabb;
			PLANE planes[6];

			void Set(f32 fovy, f32 aspect, f32 near, f32 far, const MTX34 &matrix);
			void Set(f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far, const MTX34 &matrix);
			int IntersectAABB_Ex(const AABB *otherAabb);
		};

		struct SEGMENT3 { VEC3 a, b; };
		struct LINE3 { VEC3 point, direction; };
		struct SPHERE { VEC3 point; f32 radius; };

		f32 DistSqSegment3ToSegment3(const SEGMENT3 *a, const SEGMENT3 *b, f32 *pOut1, f32 *pOut2);
		int IntersectionLine3Sphere(const LINE3 *a, const SPHERE *b, f32 *pOut1, f32 *pOut2);
		int IntersectionSegment3Sphere(const SEGMENT3 *a, const SPHERE *b, f32 *pOut1, f32 *pOut2);
		bool IntersectionAABB(const AABB *a, const AABB *b);
	}


	namespace lyt {
		class Pane;
		class DrawInfo;

		class AnimTransform;
		class AnimResource;
		class AnimationLink;
		class ResourceAccessor;
		class Group;
		class GroupContainer;

		namespace detail {
			class TexCoordAry {
			public:
				TexCoordAry();
				void Free();
				void Reserve(u8 count);
				void SetSize(u8 count);
				void Copy(const void *source, u8 count);

				u8 reservedSize, usedSize;
				void *data;
			};
		}

		class Layout {
		public:
			Layout();
			virtual ~Layout();

			virtual bool Build(const void *data, ResourceAccessor *resAcc);

			virtual AnimTransform *CreateAnimTransform();
			virtual AnimTransform *CreateAnimTransform(const void *data, ResourceAccessor *resAcc);
			virtual AnimTransform *CreateAnimTransform(const AnimResource &res, ResourceAccessor *resAcc);

			virtual void BindAnimation(AnimTransform *anim);
			virtual void UnbindAnimation(AnimTransform *anim);
			virtual void UnbindAllAnimation();
			virtual bool BindAnimationAuto(const AnimResource &res, ResourceAccessor *resAcc);

			virtual void SetAnimationEnable(AnimTransform *anim, bool unk);

			virtual void CalculateMtx(const DrawInfo &info);

			virtual void/*?*/ Draw(const DrawInfo &info);
			virtual void/*?*/ Animate(u64 flag);

			virtual void/*?*/ SetTagProcessor(ut::TagProcessorBase<wchar_t> *tagProc);

			ut::LinkList animations;

			Pane *rootPane;
			GroupContainer *groupContainer;

			float width;
			float height;
		};


		class DrawInfo {
		public:
			DrawInfo();
			virtual ~DrawInfo();

			Mtx matrix;
			float left;
			float top;
			float right;
			float bottom;
			float scaleX;
			float scaleY;
			float alpha;
			u8 _50; // this is actually a bitfield. todo: investigate how CW handles bitfields, and so on
		};


		class TexMap {
			public:
				void *image, *palette;
				u16 width, height;
				f32 minLOD, magLOD;
				u16 lodBias, palEntryNum;
				u32 settingsBitfield;

				int getFormat() { return (settingsBitfield >> 28); }
				void setFormat(int fmt) {
					settingsBitfield = (fmt << 28) | (settingsBitfield & 0xFFFFFFF);
				}

				void ReplaceImage(UnkType *tpl, unsigned long id);
		};

		class Material {
		public:
			virtual ~Material();

			// cheating a bit here
			u8 _[0x3C];
			// this is actually a pointer to more stuff, not just texmaps
			TexMap *texMaps;
		};

		class Pane {
		public:
			//Pane(nw4r::lyt::res::Pane const *); // todo: this struct
			Pane(void *);
			virtual ~Pane();

			virtual void *GetRuntimeTypeInfo() const;
			virtual void CalculateMtx(const DrawInfo &info);

			virtual void Draw(const DrawInfo &info);
			virtual void DrawSelf(const DrawInfo &info);
			virtual void Animate(u64 flag);
			virtual void AnimateSelf(u64 flag);

			virtual UnkType GetVtxColor(u64 id) const;
			virtual void SetVtxColor(u64 id, UnkType color);
			virtual u8 GetColorElement(u64 id) const;
			virtual void SetColorElement(u64 id, u8 value);
			virtual u8 GetVtxColorElement(u64 id) const;
			virtual void SetVtxColorElement(u64 id, u8 value);

			virtual Pane *FindPaneByName(const char *name, bool recursive);
			virtual Material *FindMaterialByName(const char *name, bool recursive);

			virtual void/*?*/ BindAnimation(AnimTransform *anim, bool unk1, bool unk2);
			virtual void UnbindAnimation(AnimTransform *anim, bool unk);
			virtual void UnbindAllAnimation(bool unk);
			virtual void UnbindAnimationSelf(AnimTransform *anim);

			virtual UnkType *FindAnimationLinkSelf(AnimTransform *anim);
			virtual UnkType *FindAnimationLinkSelf(const AnimResource &anim);

			virtual void SetAnimationEnable(AnimTransform *anim, bool unk1, bool unk2);
			virtual void SetAnimationEnable(const AnimResource &anim, bool unk1, bool unk2);

			virtual u64 GetMaterialNum() const;
			virtual Material *GetMaterial() const;
			virtual Material *GetMaterial(u64 id) const;

			virtual void LoadMtx(const DrawInfo &info);

			void AppendChild(Pane *child);

			UnkType GetPaneRect(const DrawInfo &info) const;

			UnkType *AddAnimationLink(AnimationLink *link);

			Vec2 GetVtxPos() const;

			u16 GetExtUserDataNum() const; // 802AC5A0


			UnkType parentLink;
			Pane *parent;

			UnkType children;
			UnkType animations;

			Material *material;

			Vec trans;
			Vec rotate;
			Vec2 scale;
			Vec2 size;

			Mtx calcMtx;
			Mtx effectiveMtx;

			float _B4;

			u8 alpha;
			u8 effectiveAlpha;
			u8 origin;
			u8 flag;

			char name[0x11];
			char userdata[9];

			u8 paneIsOwnedBySomeoneElse;
			u8 _D7;

			void SetVisible(bool value) {
				if (value)
					flag |= 1;
				else
					flag &= ~1;
			}
		};

		class TextBox : public Pane {
		public:
			TextBox(void *, void *); // todo: TextBox((res::TextBox const *,ResBlockSet const &))
			~TextBox();

			void *GetRuntimeTypeInfo() const;

			void DrawSelf(const DrawInfo &info);

			UnkType GetVtxColor(u64 id) const;
			void SetVtxColor(u64 id, UnkType color);
			u8 GetVtxColorElement(u64 id) const;
			void SetVtxColorElement(u64 id, u8 value);

			void LoadMtx(const DrawInfo &info);

			virtual void AllocStringBuffer(u16 size);
			virtual void FreeStringBuffer();

			virtual u16 SetString(const wchar_t *str, u16 destOffset = 0);
			virtual u16 SetString(const wchar_t *str, u16 destOffset, u16 length);

			wchar_t *stringBuf;

			UnkType colour1, colour2;
			void *font; // actually a ut::ResFont or whatever

			float fontSizeX, fontSizeY;
			float lineSpace, charSpace;

			void *tagProc; // actually a TagProcessor

			u16 bufferLength;
			u16 stringLength;

			u8 alignment;
			u8 flags;
		};

		class Picture : public Pane {
		public:
			Picture(void *, void *); // todo: Picture((res::Picture const *,ResBlockSet const &))
			~Picture();

			void *GetRuntimeTypeInfo() const;

			void DrawSelf(const DrawInfo &info);

			UnkType GetVtxColor(u64 id) const;
			void SetVtxColor(u64 id, UnkType color);
			u8 GetVtxColorElement(u64 id) const;
			void SetVtxColorElement(u64 id, u8 value);

			virtual void Append(const UnkType &obj);

			UnkType colours[4];
			detail::TexCoordAry texCoords;
		};
	}

}

#endif
