/* BSP file structures
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#pragma once
#include "types.h"

#define VBSP_HEADER (('V')|('B'<<8)|('S'<<16)|('P'<<24))
#define BSP_MIN 19
#define BSP_VER 21

// Limits
#define MAX_MAP_MODELS		1024
#define MAX_MAP_PLANES		65536
#define MAX_MAP_NODES		65536
#define MAX_MAP_LEAFS		65536
#define MAX_MAP_VERTS		65536
#define MAX_MAP_FACES		65536
#define MAX_MAP_ENTITIIES	8192
#define MAX_MAP_TEXINFO		12288
#define MAX_MAP_EDGES		256000
#define MAX_MAP_SURFEDGES	512000
#define MAX_MAP_LIGHTNING	0x2000000

#define MAX_MAP_BRUSHES		8192
#define MAX_MAP_TEXDATA		2048
#define MAX_MAP_DISPINFO	4096
#define MAX_MAP_AREAS		256
#define MAX_MAP_AREA_BYTES	(MAX_MAP_AREAS/8)
#define MAX_MAP_AREAPORTALS	1024

#define MAX_MAP_BRUSHIDES	65536
#define MAX_MAP_VERTNORMALS	256000
#define MAX_MAP_LEAFFACES	65536
#define MAX_MAP_LEAFBRUSHES	65536
#define MAX_MAP_PORTALS		65536
#define MAX_MAP_CLUSTERS	65536
#define MAX_MAP_LEAFWATERDATA	32768
#define MAX_MAP_PORTALVERTS	128000

#define HEADER_LUMPS		64

#define VIS_PVS 0
#define VIS_PAS 0

enum {
	LUMP_ENTITIES = 0,
	LUMP_PLANES,
	LUMP_TEXDATA,
	LUMP_VERTEXES,
	LUMP_VISIBILITY,
	LUMP_NODES,
	LUMP_TEXINFO,
	LUMP_FACES,
	LUMP_LIGHTING,
	LUMP_OCCLUSION,
	LUMP_LEAFS,
	LUMP_FACEIDS,
	LUMP_EDGES,
	LUMP_SURFEDGES,
	LUMP_MODELS,
	LUMP_WORLDLIGHTS,

	LUMP_LEAFFACES,
	LUMP_LEAFBRUSHES,
	LUMP_BRUSHES,
	LUMP_BRUSHESIDES,
	LUMP_AREAS,
	LUMP_AREAPORTALS,
	LUMP_PROPCOLLISION, // LUMP_UNUSED0
	LUMP_PROPHULLS, // LUMP_UNUSED1
	LUMP_PROPHULLVERTS, // LUMP_UNUSED2
	LUMP_PROPTRIS, // LUMP_UNUSED3
	LUMP_DISPINFO,
	LUMP_ORIGINALFACES,
	LUMP_PHYSDISP,
	LUMP_PHYSCOLLIDE,
	LUMP_VERTNORMALS,
	LUMP_VERTNORMALINDICES,

	LUMP_DISP_LIGHTMAP_ALPHAS,
	LUMP_DISP_VERTS,
	LUMP_DISP_LIGHTMAP_SAMPLE_POSITIONS,
	LUMP_GAME_LUMP,
	LUMP_LEAFWATERDATA,
	LUMP_PRIMITIVES,
	LUMP_PRIMVERTS,
	LUMP_PRIMINDICES,
	LUMP_PAKFILE,
	LUMP_CLIPPORTALVERTS,
	LUMP_CUBEMAPS,
	LUMP_TEXDATA_STRING_DATA,
	LUMP_TEXDATA_STRING_TABLE,
	LUMP_OVERLAYS,
	LUMP_LEAFMINDISTTOWATER,
	LUMP_FACE_MACRO_TEXTURE_INFO,

	LUMP_DISP_TRIS,
	LUMP_PHYSCOLLIDESURFACE,
	LUMP_WATEROVERLAYS,
	LUMP_LEAF_AMBIENT_INDEX_HDR,
	LEAF_LEAF_AMBIENT_INDEX,
	LUMP_LIGHTING_HDR,
	LUMP_WORLDLIGHTS_HDR,
	LUMP_LEAF_AMBIENT_LIGHTING_HDR,
	LUMP_LEAF_AMBIENT_LIGHTING,
	LUMP_XZIPPAKFILE, // Deprecated!
	LUMP_FACES_HDR,
	LUMP_MAP_FLAGS,
	MAP_OVERLAY_FADES,
	LUMP_OVERLAY_SYSTEM_LEVELS,
	LUMP_PHYSLEVEL,
	LUMP_DISP_MULTIBLEND
};

// Versions
enum {
	LUMP_LIGHTNING_VERSION			= 1,
	LUMP_FACES_VERSION			= 1,
	LUMP_OCCLUSION_VERSION			= 2,
	LUMP_LEAFS_VERSION			= 1,
	LUMP_LEAF_AMBIENT_LIGHTNING_VERSION	= 1,
	LUMP_WORLDLIGHTS_VERSION		= 1,
};

// Structures
#pragma pack(1)
struct BSPLump {
	u32	fileofs, size;
	u32	version;
	u32	unzipSize;
};

// Header of BSP itself
struct BSPHeader {
	u32		ident, version;
	struct BSPLump	lumps[HEADER_LUMPS];
	u32		mapRevision;
};

// Lumps
// Entity (Lump 0) is string

// Plane (Lump 1)
struct BSPPlane {
	vec3_t	normal;
	float	dist;
	u32	type;
};

// Texture data (Lump 2) contains pointer to texture and its reflectivity
struct BSPTexData {
	vec3_t	reflectivity;
	u32	index;
	u32	width, height;
	u32	viewWidth, viewHeight;
};

// Vertex (Lump 3)
struct BSPVertex {
	vec3_t	point;
};

// Visibility (Lump 4), contains compressed PVS
struct BSPVis {
	u32	clusters;
	u32	bitofs[8][2];
//	u32	byteofs[clusters][2];
};

// Node (Lump 5)
struct BSPNode {
	u32	plane;
	u32	child[2];
	i16	min[3];
	i16	max[3];
	u16	firstFace, faces;
	i16	area;
	i16	padding; // unused
};

// Texture info (Lump 6)
struct BSPTexInfo {
	float	textureVecs[2][4];
	float	lightmapVecs[2][4];
	u32	flags, texData;
};

// Face (Lump 7)
struct BSPFace {
	u16	plane;
	byte	side, onNode;
	u32	firstEdge;
	i16	edges;
	i16	texinfo, dispinfo;
	i16	surfFogVolume; // TODO:
	byte	styles[4];
	u32	lightofs;
	float	area;
	u32	lightMin[2];
	u32	lightMax[2];
	u32	origFace;
	u16	primitives;
	u16	firstPrimitive;
	u32	smoothGroup;
};

// Leaf (Lump 10)
struct BSPLeaf {
	u32	contents;
	u16	cluster;
	u16	area:9;
	u16	flags:7;
	i16	min[3];
	i16	max[3];
	u16	firstFace, faces;
	u16	firstBrush, brushes;
	i16	waterData;
};

// Edge (Lump 12)
struct BSPEdge {
	u16	v[2];
};

#pragma pack()

