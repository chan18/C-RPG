#include "game.h"
void tick_overlap(World * w)
{
	int i, j;
	w->last_obj_index =0;
	//improve later
	//can be improved by count object on creation and deletion
	for(i = 0;i<500;i++)
	{
		if(w->objs[i].exist == 1)
			w->last_obj_index++;
		else
			break;
	}
	int max_i = w->last_obj_index;
	
	for (i = 0; i <= max_i; i++) {
		for (j = 0; j < max_i; j++) {
			Object *obj = &(w->objs[i]);
			Object *obj2 = &(w->objs[j]);

			if (obj->exist == 0)
				continue;
			if (obj2->exist == 0)
				continue;
			if (obj != obj2 &&
			    obj->x == obj2->x && obj->y == obj2->y
			    && obj->overlap_fn != 0) {
				obj->overlap_fn(obj, obj2);
			}
		}
	}
}

void tick_self(World * w)
{
	int i;
	for (i = 0; i < 500; i++) {
		Object *obj = &(w->objs[i]);

		if (obj->exist == 0)
			continue;
		if (obj->tick_fn != 0)
			obj->tick_fn(obj);
		if ((obj->hp <= 0) && (obj->exist == 1))
		{
				if (obj->death_fn != 0)
					obj->death_fn(obj);

				delete_object(obj);

		}
	}
}

void tick(World * w)
{
	tick_self(w);
	tick_overlap(w);
}
