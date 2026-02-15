#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

typedef void MetaDisplay;
typedef struct _MetaWindow MetaWindow;
typedef void ClutterEvent;
typedef unsigned int guint32;

static double current_multiplier = 1.0;

// Hook on focus change
void meta_display_set_input_focus(MetaDisplay *display, MetaWindow *window, guint32 timestamp) {
    static void (*orig_set_focus)(MetaDisplay*, MetaWindow*, guint32) = NULL;
    static const char* (*get_wm_class)(MetaWindow*) = NULL;

    if (!orig_set_focus) {
        orig_set_focus = dlsym(RTLD_NEXT, "meta_display_set_input_focus");
        get_wm_class = dlsym(RTLD_NEXT, "meta_window_get_wm_class");
    }

    orig_set_focus(display, window, timestamp);

    if (window && get_wm_class) {
        const char *cls = get_wm_class(window);
        
        // RULES
        if (cls) {
            if (strcasestr(cls, "chrome")) current_multiplier = 0.1;
            else current_multiplier = 1.0;
        }
    } else {
        current_multiplier = 1.0;
    }
}

// hook event sender
void clutter_event_get_scroll_delta(const ClutterEvent *event, double *dx, double *dy) {
    static void (*orig_scroll)(const ClutterEvent*, double*, double*) = NULL;
    if (!orig_scroll) orig_scroll = dlsym(RTLD_NEXT, "clutter_event_get_scroll_delta");

    orig_scroll(event, dx, dy);

    if (dx) *dx *= current_multiplier;
    if (dy) *dy *= current_multiplier;
}
