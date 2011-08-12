/***********************************************************
* This file is part of glyr
* + a commnadline tool and library to download various sort of musicrelated metadata.
* + Copyright (C) [2011]  [Christopher Pahl]
* + Hosted at: https://github.com/sahib/glyr
*
* glyr is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* glyr is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with glyr. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/

#ifndef TAGS_MUSICBRAINZ_H
#define TAGS_MUSICBRAINT_H

#include "../../core.h"
const char *   tags_musicbrainz_url(GlyrQuery * s);
GList * tags_musicbrainz_parse(cb_object * capo);

GlyrMemCache * generic_musicbrainz_parse(cb_object * capo, const char * include);
const char * get_mbid_from_xml(GlyrQuery * s, GlyrMemCache * c, size_t * offset);
const char * generic_musicbrainz_url(GlyrQuery * sets);

#endif
