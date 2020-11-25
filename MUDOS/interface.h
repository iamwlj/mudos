#include "lpc_to_c.h"

#ifdef LPC_TO_C
typedef struct {
    char *fname;
    void (**jump_table) ();
    string_switch_entry_t **string_switch_tables;
} _interface_t;

extern _interface_t *_interface[];
#endif
