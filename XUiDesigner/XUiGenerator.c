/*
 *                           0BSD 
 * 
 *                    BSD Zero Clause License
 * 
 *  Copyright (c) 2021 Hermann Meyer
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.

 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

#include "XUiGenerator.h"
#include "XUiGridControl.h"


/*---------------------------------------------------------------------
-----------------------------------------------------------------------    
                print widgets on exit
-----------------------------------------------------------------------
----------------------------------------------------------------------*/

void remove_from_list(XUiDesigner *designer, Widget_t *wid) {
    designer->controls[wid->data].wid = NULL;
    designer->controls[wid->data].have_adjustment = false;
    free(designer->controls[wid->data].image);
    designer->controls[wid->data].image = NULL;
    designer->controls[wid->data].grid_snap_option = 0;
}

void add_to_list(XUiDesigner *designer, Widget_t *wid, const char* type,
                                    bool have_adjustment, WidgetType is_type) {
    designer->controls[wid->data].wid = wid;
    designer->controls[wid->data].type = type;
    designer->controls[wid->data].have_adjustment = have_adjustment;
    designer->controls[wid->data].is_type = is_type;
}

void print_colors(XUiDesigner *designer) {
    Xputty * main = designer->w->app;
    Colors *c = &main->color_scheme->normal;
    printf (
    "void set_costum_theme(Xputty *main) {\n"
    "    main->color_scheme->normal = (Colors) {\n"
    "         /* cairo    / r  / g  / b  / a  /  */\n"
    "        .fg =       { %.3f, %.3f, %.3f, %.3f},\n"
    "        .bg =       { %.3f, %.3f, %.3f, %.3f},\n"
    "        .base =     { %.3f, %.3f, %.3f, %.3f},\n"
    "        .text =     { %.3f, %.3f, %.3f, %.3f},\n"
    "        .shadow =   { %.3f, %.3f, %.3f, %.3f},\n"
    "        .frame =    { %.3f, %.3f, %.3f, %.3f},\n"
    "        .light =    { %.3f, %.3f, %.3f, %.3f}\n"
    "    };\n\n",c->fg[0],c->fg[1],c->fg[2],c->fg[3],
                c->bg[0],c->bg[1],c->bg[2],c->bg[3],
                c->base[0],c->base[1],c->base[2],c->base[3],
                c->text[0],c->text[1],c->text[2],c->text[3],
                c->shadow[0],c->shadow[1],c->shadow[2],c->shadow[3],
                c->frame[0],c->frame[1],c->frame[2],c->frame[3],
                c->light[0],c->light[1],c->light[2],c->light[3]);

    c = &main->color_scheme->prelight;
    printf (
    "    main->color_scheme->prelight = (Colors) {\n"
    "         /* cairo    / r  / g  / b  / a  /  */\n"
    "        .fg =       { %.3f, %.3f, %.3f, %.3f},\n"
    "        .bg =       { %.3f, %.3f, %.3f, %.3f},\n"
    "        .base =     { %.3f, %.3f, %.3f, %.3f},\n"
    "        .text =     { %.3f, %.3f, %.3f, %.3f},\n"
    "        .shadow =   { %.3f, %.3f, %.3f, %.3f},\n"
    "        .frame =    { %.3f, %.3f, %.3f, %.3f},\n"
    "        .light =    { %.3f, %.3f, %.3f, %.3f}\n"
    "    };\n\n",c->fg[0],c->fg[1],c->fg[2],c->fg[3],
                c->bg[0],c->bg[1],c->bg[2],c->bg[3],
                c->base[0],c->base[1],c->base[2],c->base[3],
                c->text[0],c->text[1],c->text[2],c->text[3],
                c->shadow[0],c->shadow[1],c->shadow[2],c->shadow[3],
                c->frame[0],c->frame[1],c->frame[2],c->frame[3],
                c->light[0],c->light[1],c->light[2],c->light[3]);

    c = &main->color_scheme->selected;
    printf (
    "    main->color_scheme->selected = (Colors) {\n"
    "         /* cairo    / r  / g  / b  / a  /  */\n"
    "        .fg =       { %.3f, %.3f, %.3f, %.3f},\n"
    "        .bg =       { %.3f, %.3f, %.3f, %.3f},\n"
    "        .base =     { %.3f, %.3f, %.3f, %.3f},\n"
    "        .text =     { %.3f, %.3f, %.3f, %.3f},\n"
    "        .shadow =   { %.3f, %.3f, %.3f, %.3f},\n"
    "        .frame =    { %.3f, %.3f, %.3f, %.3f},\n"
    "        .light =    { %.3f, %.3f, %.3f, %.3f}\n"
    "    };\n\n",c->fg[0],c->fg[1],c->fg[2],c->fg[3],
                c->bg[0],c->bg[1],c->bg[2],c->bg[3],
                c->base[0],c->base[1],c->base[2],c->base[3],
                c->text[0],c->text[1],c->text[2],c->text[3],
                c->shadow[0],c->shadow[1],c->shadow[2],c->shadow[3],
                c->frame[0],c->frame[1],c->frame[2],c->frame[3],
                c->light[0],c->light[1],c->light[2],c->light[3]);

    c = &main->color_scheme->active;
    printf (
    "    main->color_scheme->active = (Colors) {\n"
    "         /* cairo    / r  / g  / b  / a  /  */\n"
    "        .fg =       { %.3f, %.3f, %.3f, %.3f},\n"
    "        .bg =       { %.3f, %.3f, %.3f, %.3f},\n"
    "        .base =     { %.3f, %.3f, %.3f, %.3f},\n"
    "        .text =     { %.3f, %.3f, %.3f, %.3f},\n"
    "        .shadow =   { %.3f, %.3f, %.3f, %.3f},\n"
    "        .frame =    { %.3f, %.3f, %.3f, %.3f},\n"
    "        .light =    { %.3f, %.3f, %.3f, %.3f}\n"
    "    };\n\n",c->fg[0],c->fg[1],c->fg[2],c->fg[3],
                c->bg[0],c->bg[1],c->bg[2],c->bg[3],
                c->base[0],c->base[1],c->base[2],c->base[3],
                c->text[0],c->text[1],c->text[2],c->text[3],
                c->shadow[0],c->shadow[1],c->shadow[2],c->shadow[3],
                c->frame[0],c->frame[1],c->frame[2],c->frame[3],
                c->light[0],c->light[1],c->light[2],c->light[3]);

    c = &main->color_scheme->insensitive;
    printf (
    "    main->color_scheme->insensitive = (Colors) {\n"
    "         /* cairo    / r  / g  / b  / a  /  */\n"
    "        .fg =       { %.3f, %.3f, %.3f, %.3f},\n"
    "        .bg =       { %.3f, %.3f, %.3f, %.3f},\n"
    "        .base =     { %.3f, %.3f, %.3f, %.3f},\n"
    "        .text =     { %.3f, %.3f, %.3f, %.3f},\n"
    "        .shadow =   { %.3f, %.3f, %.3f, %.3f},\n"
    "        .frame =    { %.3f, %.3f, %.3f, %.3f},\n"
    "        .light =    { %.3f, %.3f, %.3f, %.3f}\n"
    "    };\n"
    "}\n\n",c->fg[0],c->fg[1],c->fg[2],c->fg[3],
            c->bg[0],c->bg[1],c->bg[2],c->bg[3],
            c->base[0],c->base[1],c->base[2],c->base[3],
            c->text[0],c->text[1],c->text[2],c->text[3],
            c->shadow[0],c->shadow[1],c->shadow[2],c->shadow[3],
            c->frame[0],c->frame[1],c->frame[2],c->frame[3],
            c->light[0],c->light[1],c->light[2],c->light[3]);

}

const char* parse_adjusment_type(CL_type cl_type) {
    switch(cl_type) {
        case CL_NONE:            return "CL_NONE";
        break;
        case CL_CONTINUOS:       return "CL_CONTINUOS";
        break;
        case CL_TOGGLE:          return "CL_TOGGLE";
        break;
        case CL_BUTTON:          return "CL_BUTTON";
        break;
        case CL_ENUM:            return "CL_ENUM";
        break;
        case CL_VIEWPORT:        return "CL_VIEWPORT";
        break;
        case CL_METER:           return "CL_METER";
        break;
        case CL_LOGARITHMIC:     return "CL_LOGARITHMIC";
        break;
        case CL_LOGSCALE:        return "CL_LOGSCALE";
        break;
        case CL_VIEWPORTSLIDER:  return "CL_VIEWPORTSLIDER";
        break;
        default: return NULL;
    }
}

void print_list(XUiDesigner *designer) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    bool have_image = false;
    for (;i<MAX_CONTROLS;i++) {
        if (designer->controls[i].wid != NULL && (designer->controls[i].is_type != IS_FRAME &&
                                                designer->controls[i].is_type != IS_TABBOX)) {
            j++;
        } else if (designer->controls[i].wid != NULL && (designer->controls[i].is_type == IS_FRAME ||
                                                        designer->controls[i].is_type == IS_TABBOX)) {
            k++;
            if (designer->controls[i].is_type == IS_TABBOX) {
                l += designer->controls[i].wid->childlist->elem;
            }
        }
        if (designer->controls[i].image) {
            have_image = true;
        }
    }
    if (j) {
        Window w = (Window)designer->ui->widget;
        char *name;
        XFetchName(designer->ui->app->dpy, w, &name);

        printf ("\n#define CONTROLS %i\n", j);
        printf ("\n#define GUI_ELEMENTS %i\n\n", k);
        printf ("\n#define TAB_ELEMENTS %i\n\n", l);
        printf ("\n#define PLUGIN_UI_URI \"%s\"\n\n",designer->lv2c.ui_uri);
        printf ("\n#include \"lv2_plugin.h\"\n\n");
        if (have_image) printf ("\n#include \"xresources.h\"\n\n");
        print_colors(designer);
        printf ("#include \"%s\"\n\n\n"
        "void plugin_value_changed(X11_UI *ui, Widget_t *w, PortIndex index) {\n"
        "    // do special stuff when needed\n"
        "}\n\n"
        "void plugin_set_window_size(int *w,int *h,const char * plugin_uri) {\n"
        "    (*w) = %i; //set initial width of main window\n"
        "    (*h) = %i; //set initial height of main window\n"
        "}\n\n"
        "const char* plugin_set_name() {\n"
        "    return \"%s\"; //set plugin name to display on UI\n"
        "}\n\n"
        "void plugin_create_controller_widgets(X11_UI *ui, const char * plugin_uri) {\n"
        "    set_costum_theme(&ui->main);\n"
        , designer->run_test? "ui_test.cc": "lv2_plugin.cc", designer->ui->width, designer->ui->height, name? name:"Test");
        if (designer->image != NULL) {
            if (designer->run_test) {
                printf ("    load_bg_image(ui,\"%s\");\n", designer->image);
            } else {
                printf ("    load_bg_image(ui,\"./resources/%s\");\n", basename(designer->image));
            }
        }

    } else {
        return;
    }
    i = 0;
    j = 0;
    l = 0;
    int ttb[k] ;
    memset(ttb, 0, k*sizeof(int));
    for (;i<MAX_CONTROLS;i++) {
        if (designer->controls[i].wid != NULL) {
            if (designer->controls[i].is_type == IS_FRAME) {
                printf ("    ui->elem[%i] = %s (ui->elem[%i], ui->win, %i, \"%s\", ui, %i,  %i, %i, %i);\n", 
                    j, designer->controls[i].type, j,
                    designer->controls[i].port_index, designer->controls[i].wid->label,
                    designer->controls[i].wid->x, designer->controls[i].wid->y,
                    designer->controls[i].wid-> width, designer->controls[i].wid->height);
                if (designer->controls[i].image != NULL ) {
                    if (designer->run_test) {
                        printf ("    load_controller_image(ui->elem[%i], \"%s\");\n",
                                            j, designer->controls[i].image);
                    } else {
                        char * xldl = strdup(basename(designer->controls[i].image));
                        strdecode(xldl, ".", "_");
                        printf ("    widget_get_png(ui->elem[%i], LDVAR(%s));\n",
                                j, xldl);
                        free(xldl);
                       // printf ("    load_controller_image(ui->elem[%i], \"./resources/%s\");\n",
                       //                         j, basename(designer->controls[i].image));
                    }
                }
                j++;
            } else if (designer->controls[i].is_type == IS_TABBOX) {
                printf ("    ui->elem[%i] = %s (ui->elem[%i], ui->win, %i, \"%s\", ui, %i,  %i, %i, %i);\n", 
                    j, designer->controls[i].type, j,
                    designer->controls[i].port_index, designer->controls[i].wid->label,
                    designer->controls[i].wid->x, designer->controls[i].wid->y,
                    designer->controls[i].wid-> width, designer->controls[i].wid->height);
                ttb[j] = l;
                int elem = designer->controls[i].wid->childlist->elem;
                int t = 0;
                for(;t<elem;t++) {
                    Widget_t *wi = designer->controls[i].wid->childlist->childs[t];
                    printf ("    ui->tab_elem[%i] = add_lv2_tab (ui->tab_elem[%i], ui->elem[%i], -1, \"%s\", ui);\n", 
                        l, l, j, wi->label);
                    l++;
                }
                printf ("\n");
                j++;
            }
            
        }
    }
    i = 0;
    j = 0;
    for (;i<MAX_CONTROLS;i++) {
        if (designer->controls[i].wid != NULL) {
            Widget_t * wid = designer->controls[i].wid;
            if (designer->controls[i].is_type == IS_FRAME ||
                designer->controls[i].is_type == IS_TABBOX) {
                continue;
            } else {
                char* parent = NULL;
                if (designer->controls[i].in_tab) {
                    int atb = ttb[designer->controls[i].in_frame-1];
                    asprintf(&parent,"ui->tab_elem[%i]", atb + designer->controls[i].in_tab-1);
                } else {
                    designer->controls[i].in_frame ? asprintf(&parent,"ui->elem[%i]", designer->controls[i].in_frame-1) :
                        asprintf(&parent,"%s", "ui->win");
                }
                printf ("    ui->widget[%i] = %s (ui->widget[%i], %s, %i, \"%s\", ui, %i,  %i, %i, %i);\n", 
                    j, designer->controls[i].type, j, parent,
                    designer->controls[i].port_index, designer->controls[i].wid->label,
                    designer->controls[i].wid->x, designer->controls[i].wid->y,
                    designer->controls[i].wid-> width, designer->controls[i].wid->height);
                free(parent);
            }
            if (designer->controls[i].is_atom_patch && designer->controls[i].is_type != IS_FILE_BUTTON) {
                const char* uri = (const char*) wid->parent_struct;
                printf("    ui->widget[%i]->parent_struct = (void*)\"%s\";\n", j, uri);
            }
            if (designer->controls[i].image != NULL ) {
                if (designer->run_test) {
                    printf ("    load_controller_image(ui->widget[%i], \"%s\");\n",
                            j, designer->controls[i].image);
                } else {
                    char * xldl = strdup(basename(designer->controls[i].image));
                    strdecode(xldl, ".", "_");
                    printf ("    widget_get_png(ui->widget[%i], LDVAR(%s));\n",
                    //printf ("    load_controller_image(ui->widget[%i], \"./resources/%s\");\n",
                            j, xldl);
                    free(xldl);
                }
            }
            if (designer->controls[i].is_type == IS_COMBOBOX) {
                Widget_t *menu = wid->childlist->childs[1];
                Widget_t* view_port =  menu->childlist->childs[0];
                ComboBox_t *comboboxlist = (ComboBox_t*)view_port->parent_struct;
                unsigned int k = 0;
                for(; k<comboboxlist->list_size;k++) {
                    printf ("    combobox_add_entry (ui->widget[%i], \"%s\");\n", j, comboboxlist->list_names[k]);
                }
            }
            if (designer->controls[i].have_adjustment) {
                if (wid->adj->type == CL_LOGARITHMIC) {
                    printf ("    set_adjustment(ui->widget[%i]->adj, %.3f, %.3f, %.3f, %.3f, %.3f, %s);\n", 
                        j, powf(10,wid->adj->std_value), powf(10,wid->adj->std_value), powf(10,wid->adj->min_value),
                        powf(10,wid->adj->max_value), wid->adj->step, parse_adjusment_type(wid->adj->type));
                    
                } else if (wid->adj->type == CL_LOGSCALE) {
                    printf ("    set_adjustment(ui->widget[%i]->adj, %.3f, %.3f, %.3f, %.3f, %.3f, %s);\n", 
                        j, log10(wid->adj->std_value)*wid->adj->log_scale, log10(wid->adj->std_value)*wid->adj->log_scale,
                        log10(wid->adj->min_value)*wid->adj->log_scale, log10(wid->adj->max_value)*wid->adj->log_scale,
                        wid->adj->step, parse_adjusment_type(wid->adj->type));
                    
                } else {
                    printf ("    set_adjustment(ui->widget[%i]->adj, %.3f, %.3f, %.3f, %.3f, %.3f, %s);\n", 
                        j, wid->adj->std_value, wid->adj->std_value, wid->adj->min_value, wid->adj->max_value,
                        wid->adj->step, parse_adjusment_type(wid->adj->type));
                }
            }
            printf ("\n");
            if (designer->controls[i].is_type != IS_FRAME) j++;
        }
    }
    printf ("}\n\n"
    "void plugin_cleanup(X11_UI *ui) {\n"
    "    // clean up used sources when needed\n"
    "}\n\n"

    "void plugin_port_event(LV2UI_Handle handle, uint32_t port_index,\n"
    "                        uint32_t buffer_size, uint32_t format,\n"
    "                        const void * buffer) {\n"
    "    // port value change message from host\n"
    "    // do special stuff when needed\n"
    "}\n\n");

}

void run_save(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    XUiDesigner *designer = (XUiDesigner*)w->parent_struct;
    if (w->flags & HAS_POINTER && !adj_get_value(w->adj_y)) {
        int i = 0;
        int j = 0;
        bool have_image = false;
        for (;i<MAX_CONTROLS;i++) {
            if (designer->controls[i].wid != NULL) {
                j++;
            }
            if (designer->controls[i].image) {
                have_image = true;
            }
        }
        if (!j) {
            Widget_t *dia = open_message_dialog(designer->ui, INFO_BOX, _("INFO"),
                                            _("Please create at least one Controller,|or load a LV2 URI to save a build "),NULL);
            XSetTransientForHint(w->app->dpy, dia->widget, designer->ui->widget);
            return;
        }
        Window w = (Window)designer->ui->widget;
        char *name = NULL;
        XFetchName(designer->ui->app->dpy, w, &name);
        if (name == NULL) asprintf(&name, "%s", "noname");
        char* filepath = NULL;
        asprintf(&filepath, "./Bundle/save.lv2/%s_ui",name);
        struct stat st = {0};

        if (stat(filepath, &st) == -1) {
            mkdir(filepath, 0700);
        }

        char* filename = NULL;
        asprintf(&filename, "./Bundle/save.lv2/%s_ui/%s.c",name, name );
        remove (filename);
        FILE *fp;
        if((fp=freopen(filename, "w" ,stdout))==NULL) {
            printf("open failed\n");
        }
        fprintf(stderr, "save to %s\n", filename);
        print_list(designer);
        fclose(fp);
        free(filename);
        if (system(NULL)) {
            char* cmd = NULL;
            asprintf(&cmd, "cp ./Bundle/wrapper/libxputty/* \'%s\'", filepath);
            int ret = system(cmd);
            if (!ret) {
                free(cmd);
                asprintf(&cmd,"\n\n	# check LD version\n"
                    "	ifneq ($(shell $(LD) --version 2>&1 | head -n 1 | grep LLD),)\n"
                    "		ifneq ($(shell uname -a | grep  x86_64), )\n"
                    "			LDEMULATION := elf_x86_64\n"
                    "		else ifneq ($(shell uname -a | grep i386), )\n"
                    "			LDEMULATION := elf_i386\n"
                    "		endif\n"
                    "		USE_LDD = 1\n"
                    "	endif\n"

                    "\n\n	NAME = %s\n"
                    "	space := $(subst ,, )\n"
                    "	EXEC_NAME := $(subst $(space),_,$(NAME))\n"
                    "	RESOURCES_DIR :=./resources/\n"
                    "	LIB_DIR := ../../../libxputty/libxputty/\n"
                    "	HEADER_DIR := $(LIB_DIR)include/\n"
                    "	UI_LIB:= $(LIB_DIR)libxputty.a\n"
                    "	STRIP ?= strip\n\n"
                    "	RESOURCES := $(wildcard $(RESOURCES_DIR)*.png)\n"
                    "	RESOURCES_OBJ := $(notdir $(patsubst %s.png,%s.o,$(RESOURCES)))\n"
                    "	RESOURCES_LIB := $(notdir $(patsubst %s.png,%s.a,$(RESOURCES)))\n"
                    "	RESOURCE_EXTLD := $(notdir $(patsubst %s.png,%s_png,$(RESOURCES)))\n"
                    "	RESOURCEHEADER := xresources.h\n"
                    "	LDFLAGS += -fvisibility=hidden `pkg-config --cflags --libs cairo x11 lilv-0` \\\n"
                    "	-shared -lm -fPIC -Wl,-z,noexecstack -Wl,--no-undefined -Wl,--gc-sections\n"
                    "	CFLAGS := -O2 -D_FORTIFY_SOURCE=2 -Wall -fstack-protector -fvisibility=hidden \\\n"
                    "	-fdata-sections -Wl,--gc-sections -Wl,-z,relro,-z,now -Wl,--exclude-libs,ALL\n\n"
                    ".PHONY : all\n\n"
                    ".NOTPARALLEL:\n\n"
                    "all: $(RESOURCEHEADER) $(EXEC_NAME)\n\n"
                    "$(RESOURCEHEADER): $(RESOURCES_OBJ)\n"
                    "	rm -f $(RESOURCEHEADER)\n"
                    "	for f in $(RESOURCE_EXTLD); do \\\n"
                    "		echo 'EXTLD('$${f}')' >> $(RESOURCEHEADER) ; \\\n"
                    "	done\n\n"
                    "ifdef USE_LDD\n"
                    "$(RESOURCES_OBJ): $(RESOURCES)\n"
                    "	cd $(RESOURCES_DIR) && $(LD) -r -b binary -m $(LDEMULATION) -z noexecstack $(patsubst %s.o,%s.png,$@) -o ../$@\n"
                    "	$(AR) rcs $(patsubst %s.o,%s.a,$@) $@\n"
                    "else\n"
                    "$(RESOURCES_OBJ): $(RESOURCES)\n"
                    "	cd $(RESOURCES_DIR) && $(LD) -r -b binary -z noexecstack --strip-all $(patsubst %s.o,%s.png,$@) -o ../$@\n"
                    "	$(AR) rcs $(patsubst %s.o,%s.a,$@) $@\n"
                    "endif\n\n"
                    "$(EXEC_NAME):$(RESOURCES_OBJ)\n"
                    "	$(CC) $(CFLAGS) \'$(NAME).c\' -L. $(RESOURCES_LIB) $(UI_LIB) -o \'$(EXEC_NAME)_ui.so\' $(LDFLAGS) -I./ -I$(HEADER_DIR)\n"
                    "	$(STRIP) -s -x -X -R .comment -R .note.ABI-tag $(EXEC_NAME)_ui.so\n\n"
                    "clean:\n"
                    "	rm -f *.a *.o *.so xresources.h\n\n",
                    name, "%%","%%","%%","%%","%%","%%","%%","%%","%%","%%","%%","%%","%%","%%");
                char* makefile = NULL;
                asprintf(&makefile, "%s/makefile",filepath);
                FILE *fpm;
                if((fpm=freopen(makefile, "w" ,stdout))==NULL) {
                    printf("open failed\n");
                }
                printf(cmd);
                fclose(fpm);
                free(makefile);
                free(cmd);
                cmd = NULL;
                //asprintf(&cmd, "cd \'%s\'  && make", filepath);
                //ret = system(cmd);
                //free(cmd);
                //cmd = NULL;
            } else {
                free(cmd);
            }
        }
        free(filepath);
        
        char* cmd = NULL;
        if (have_image || designer->image != NULL) {
            filepath = NULL;
            asprintf(&filepath, "./Bundle/save.lv2/%s_ui/resources",name);
            if (stat(filepath, &st) == -1) {
                mkdir(filepath, 0700);
            } else {
                asprintf(&cmd, "rm -rf \'%s\'", filepath);
                int ret = system(cmd);
                if (!ret) {
                    free(cmd);
                    cmd = NULL;
                    mkdir(filepath, 0700);
                } else {
                    free(cmd);
                    cmd = NULL;
                }
            }
        }
        if (designer->image != NULL) {
            asprintf(&cmd, "cp \'%s\' \'%s\'", designer->image,filepath);
            int ret = system(cmd);
            if (!ret) {
                free(cmd);
                cmd = NULL;
            } else {
                free(cmd);
                cmd = NULL;
                fprintf(stderr, "Fail to copy image\n");
            }
        }
        if (have_image) {
            i = 0;
            for (;i<MAX_CONTROLS;i++) {
                if (designer->controls[i].image != NULL) {
                    asprintf(&cmd, "cp \'%s\' \'%s\'", designer->controls[i].image,filepath);
                    int ret = system(cmd);
                    if (!ret) {
                        free(cmd);
                        cmd = NULL;
                    } else {
                        free(cmd);
                        cmd = NULL;
                        fprintf(stderr, "Fail to copy image\n");
                    }
                }
            }
            free(filepath);
            free(name);
        }
    }
}

void run_test(void *w_, void* user_data) {
    Widget_t *w = (Widget_t*)w_;
    XUiDesigner *designer = (XUiDesigner*)w->parent_struct;
    if (w->flags & HAS_POINTER && !adj_get_value(w->adj_y)) {
        int i = 0;
        int j = 0;
        for (;i<MAX_CONTROLS;i++) {
            if (designer->controls[i].wid != NULL) {
                j++;
            }
        }
        if (!j) {
            Widget_t *dia = open_message_dialog(designer->ui, INFO_BOX, _("INFO"),
                                            _("Please create at least one Controller,|or load a LV2 URI to run a test build "),NULL);
            XSetTransientForHint(w->app->dpy, dia->widget, designer->ui->widget);
            return;
        }
        designer->run_test = true;
        char* name = "./Bundle/test.lv2/test/test.c";
        remove (name);
        FILE *fp;
        if((fp=freopen(name, "w" ,stdout))==NULL) {
            printf("open failed\n");
        }

        print_list(designer);
        fclose(fp);
        if (system(NULL)) {
            if ((int)adj_get_value(designer->color_chooser->adj)) {
                adj_set_value(designer->color_chooser->adj, 0.0);
            }
            widget_hide(designer->w);
            widget_hide(designer->ui);
            XFlush(designer->w->app->dpy);
            int ret = system("cd ./Bundle/test.lv2/test  && "
                "cc -O2 -D_FORTIFY_SOURCE=2 -Wall -fstack-protector "
                "`pkg-config lilv-0 --cflags` test.c -L. ../../../libxputty/libxputty/libxputty.a "
                "-o uitest  -fPIC -Wl,-z,noexecstack -Wl,--no-undefined -I./ -I../../../libxputty/libxputty/include/ "
                "`pkg-config --cflags --libs cairo x11 lilv-0` -lm ");
            if (!ret) {
                ret = system("cd ./Bundle/test.lv2/test  && ./uitest");
            }
            if (!ret) {
                designer->run_test = false;
                widget_show_all(designer->w);
                widget_show_all(designer->ui);
                use_grid(designer->grid, NULL);
                widget_hide(designer->controller_settings);
                widget_hide(designer->combobox_settings);
            } else {
                designer->run_test = false;
                widget_show_all(designer->w);
                widget_show_all(designer->ui);
                use_grid(designer->grid, NULL);
                widget_hide(designer->controller_settings);
                widget_hide(designer->combobox_settings);
                Widget_t *dia = open_message_dialog(designer->ui, INFO_BOX, _("INFO"),
                                                _("Test fail, sorry"),NULL);
                XSetTransientForHint(w->app->dpy, dia->widget, designer->ui->widget);
            }
        }
    }
}
