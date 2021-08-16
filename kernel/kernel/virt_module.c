/* Virtual Modules (V-Module) */

#include <kernel/virt_module.h>
#include <stdint.h>
#include <string.h>
#include <vga/vga.h>

#define MAX_MODULES 10

int next_index = 0;

struct virt_module *virt_modules[MAX_MODULES];

/* add_module()
 * Adds a module to the virt_modules array
 */
int add_module(char name[], char license[]) {

  strcpy(virt_modules[next_index]->module_name, name);
  strcpy(virt_modules[next_index]->module_license, license);
  virt_modules[next_index]->is_loaded = 1;

  check_module_license(name);

  // writestr("Added module %s , License - %s. Index %d\n",
  // virt_modules[next_index-1]->module_name,
  // virt_modules[next_index-1]->module_license, next_index);

  next_index++;
  return 0;
}

/* remove_module()
 * Removes a module
 */
int remove_module(char name[]) {
  int i;
  for (i = 0; i < 10; i++) {
    if (strcmp(virt_modules[i]->module_name, name) == 0) {
      writestr("Removed module %s\n", virt_modules[i]->module_name);
      strcpy(virt_modules[i]->module_name, "");
      strcpy(virt_modules[i]->module_license, "");
      virt_modules[i]->is_loaded = 0;
      return 0;
    } else {
      writestr("Module %s not loaded\n", name);
      return 1;
    }
  }
}

/* check_module_license()
 * Checks the module license
 */
int check_module_license(char name[]) {
}
