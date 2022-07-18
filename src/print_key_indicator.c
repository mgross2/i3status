
#include <stdlib.h>

#include <yajl/yajl_gen.h>
#include <yajl/yajl_version.h>

#include <X11/extensions/XKB.h>
#include <X11/XKBlib.h>

#include "i3status.h"

#define NUM_INDS 3
#define STRING_SIZE 6

void print_key_indicator(key_indicator_ctx_t *ctx) {
	
	char *outwalk = ctx->buf;
	char *ind_names[NUM_INDS] = {"Num Lock", "Caps Lock", "Scroll Lock"};
	char indicator_string[STRING_SIZE];
	char indicator_chars[3];
	int i;
	int ndx = 0;
		
	Atom iatoms[NUM_INDS] = {0};
	Bool state[NUM_INDS] = {0};

	Display *dpy = XOpenDisplay(NULL); 

	for (i = 0; i < NUM_INDS; i++) {
		iatoms[i] = XInternAtom(dpy, ind_names[i], 0);
	}
		
	for (i = 0; i < NUM_INDS; i++) {
		XkbGetNamedIndicator(dpy, iatoms[i], &ndx, &state[i], NULL, NULL);
	}

	indicator_chars[0] = state[0] ? 'N' : 'n';
	indicator_chars[1] = state[1] ? 'C' : 'c';
	indicator_chars[2] = state[2] ? 'S' : 's';

	snprintf(indicator_string, STRING_SIZE, "%c %c %c", indicator_chars[0], indicator_chars[1], indicator_chars[2]);

	OUTPUT_FULL_TEXT(indicator_string);

	XCloseDisplay(dpy);
}