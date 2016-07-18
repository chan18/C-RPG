#include "game.h"
int fn_heal_timer(Object * o)
{
    o->timer -=1;
    if(o->timer <= 0)
        o->exist = 0;
}
int fn_do_rand(Object * o)
{
    int r = rand() % 50;
    if(r == 0)
    {
        obj_move(o->world,o,-1,0);
    }
    if(r == 1)
    {
        obj_move(o->world,o,1,0);
    }
    if(r == 2)
    {
        obj_move(o->world,o,0,-1);
    }
    if(r == 3)
    {
        obj_move(o->world,o,0,1);
    }
    if(r == 4)
    {
        if(rand()%10 == 0)
            new_mk_obj("bomb",o->world,o->x,o->y,o);
    }
}
int fn_fire_timer(Object* o)
{
    o->timer -=1;
    if(o->timer <= 0)
        o->exist = 0;
}
int fn_bomb_timer(Object * o)
{
    o->timer -=1;

    snprintf(o->shape.str,3,"%d",o->timer);
    if(o->timer <=0)
    {
        int cy,cx;
        for(cy = -1; cy<=1; cy++)
        {
            for(cx = -1; cx<=1; cx++)
            {
                new_mk_obj("fire",o->world,o->x + cx, o->y + cy,o);
            }
        }


        o->exist = 0;
    }

}

int fn_death_drop(Object* me)
{
    int i;
    for(i=0; i<10; i++)
    {
        char * item = &(me->item_slots[i][0]);
        if(!strcmp(item,""))
            continue;
        new_mk_obj(item,me->world,me->x,me->y,me);
    }
}

int fn_thru_bullet_timer(Object* me)
{
    me->timer--;
    if(me->timer<=0)
        me->exist=0;
    if(!strcmp(me->direction,"left"))
        obj_move(me->world,me,-1,0);
    if(!strcmp(me->direction,"right"))
        obj_move(me->world,me,1,0);
    if(!strcmp(me->direction,"up"))
        obj_move(me->world,me,0,-1);
    if(!strcmp(me->direction,"down"))
        obj_move(me->world,me,0,1);
}