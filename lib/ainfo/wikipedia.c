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
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "wikipedia.h"
#include "../core.h"
#include "../stringlib.h"

const char * ainfo_wikipedia_url(GlyQuery * s)
{
    return strdup_printf("http://%s.wikipedia.org/wiki/%%artist%%_(Band)",s->lang);

}

GlyCacheList * ainfo_wikipedia_parse(cb_object * capo)
{
    char * txt_begin = strstr(capo->cache->data,"<a href=\"#mw-head\"");
    remove_tags_from_string(txt_begin,capo->cache->size - (txt_begin - capo->cache->data),'<','>');
    puts(txt_begin);
    return NULL;
}