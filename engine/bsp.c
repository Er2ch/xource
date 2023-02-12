/* Binary Space Partitioning
 * (c) Er2 2023 <er2@dismail.de>
 * Zlib License
 */

#include "port.h"
#include "fs.h"
#include "common/dev.h"
#include "engine/bsp.h"

xbool LoadBSP(string name) {
	struct BSPHeader *header;
	file_t *file;

	file = FS_Open(name, "rb");
	if (!file) return false;

	header = (struct BSPHeader *)file->buf;

	if (header->ident != VBSP_HEADER)
		Err("Wrong map!");
	if (header->version < BSP_MIN || header->version > BSP_VER)
		Err("Wrong BSP version, expected %d, got %d", BSP_VER, header->version);

	Print("Version:	%d", header->version);
	Print("Revision:	%d", header->mapRevision);
	Print("Vertexes:	%d", header->lumps[LUMP_VERTEXES].size / sizeof(struct BSPVertex));
	Print("Edges:		%d", header->lumps[LUMP_EDGES].size / sizeof(struct BSPEdge));
	Print("Surfedges:	%d", header->lumps[LUMP_SURFEDGES].size / sizeof(int));
	Print("Texinfos:	%d", header->lumps[LUMP_TEXINFO].size / sizeof(struct BSPTexInfo));
	Print("Faces:		%d", header->lumps[LUMP_FACES].size / sizeof(struct BSPFace));

	FS_Close(file);
	return true;
}

