/**
 * @file   <nazev>.c
 * @author <Jmeno Přijmeni>
 * 
 */

#include "stm32_kit.h"


OS_TID id_task;

__task void Task() {
	for (;;) {
		//TODO
	}
}

__task void setup() {
	//TODO: setup
	
	id_task = os_tsk_create(Task, 0);
	os_tsk_delete_self();
}

int main () {
	os_sys_init(setup);
}

