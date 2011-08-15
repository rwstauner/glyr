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
#include "google.h"
#include "../../core.h"
#include "../../stringlib.h"


#define FIRST_RESULT "<a href=\"/imgres?imgurl="
#define END_OF_URL "&amp;imgrefurl="

const char * generic_google_url(GlyrQuery * sets, const char * searchterm)
{
    const char * lang = NULL;
    if(!strcasecmp(sets->lang,"us"))
        lang = "com"  ;
    else if(!strcasecmp(sets->lang,"ca"))
        lang = "ca"   ;
    else if(!strcasecmp(sets->lang,"uk"))
        lang = "co.uk";
    else if(!strcasecmp(sets->lang,"fr"))
        lang = "fr"   ;
    else if(!strcasecmp(sets->lang,"de"))
        lang = "de"   ;
    else if(!strcasecmp(sets->lang,"jp"))
        lang = "co.jp";
    else
        lang = "com";

    const char * back = NULL;

    // Only use the 'large' option if really set high (>1000), large is usually verrrry incorrrect.
    if(sets->cover.min_size == -1)
    {
        back = "islt;qsvga";
    }
    else if(sets->cover.min_size <  50 && sets->cover.max_size <= 150)
    {
        back = "isz:i";
    }
    else if(sets->cover.min_size < 150 && sets->cover.max_size <= 300)
    {
        back = "isz:s";
    }
    else if(sets->cover.min_size < 300 && sets->cover.max_size <= 1000)
    {
        back = "islt:qsvga";
    }
    else
    {
        back = "islt:vga";
    }

    return g_strdup_printf("http://www.google.%s/images?q=%s&safe=off&tbs=isch:1,iar:s,%s",lang,searchterm,back);
}

const char * cover_google_url(GlyrQuery * s)
{
    const char * result = NULL;
    char * searchterm = strdup("%artist%+%album%+album");
    if(searchterm != NULL)
    {
        result = generic_google_url(s,searchterm);
        g_free(searchterm);
    }
    return result;
}

GList * generic_google_parse(cb_object * capo)
{
    GList * r_list = NULL;

    size_t urlc = 0;
    char * find = capo->cache->data;

    while( (find =  strstr(find+1,FIRST_RESULT)) != NULL && continue_search(urlc,capo->s))
    {
        char * end_of_url;
        find += strlen(FIRST_RESULT);
        if((end_of_url = strstr(find, END_OF_URL)) != NULL)
        {
            char * url = copy_value(find,end_of_url);
            if(url)
            {
                GlyrMemCache * result = DL_init();
                result->data = url;

                result->size = end_of_url - find;
                r_list = g_list_prepend(r_list,result);
                urlc++;
            }
        }
    }
    return r_list;
}

GList * cover_google_parse(cb_object * capo)
{
    return generic_google_parse(capo);
}

MetaDataSource cover_google_src =
{
    .name      = "google",
    .key       = 'g',
    .parser    = cover_google_parse,
    .get_url   = cover_google_url,
    .type      = GET_COVERART,
    .quality   = 35,
    .speed     = 99,
    .endmarker = NULL,
    .free_url  = true
};