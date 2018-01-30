/*
 * This file is part of "2º Projeto de Introdução à Computação 2017/2018"
 * (2oPIC1718).
 *
 * 2oPIC1718 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * 2oPIC1718 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 2oPIC1718. If not, see <http://www.gnu.org/licenses/>.
 * */

/**
 * @file
 * This file is an example of: a) how to use the API defined in the
 * showworld.h header (mandatory for the project); and, b) how to use the
 * concrete simple implementation of the API (provided by the
 * showworld_simple.c file).
 *
 * @author Nuno Fachada
 * @date 2018
 * @copyright [GNU General Public License version 3 (GPLv3)](http://www.gnu.org/licenses/gpl.html)
 * */

#include "showworld.h"
#include "shuffle.h"
#include "ini.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/** Horizontal world size. */
#define WORLD_X 20
/** Vertical world size. */
#define WORLD_Y 20



/**
 * Structure defining agent properties.
 *
 * @note This is an example which will probably not work in a fully functional
 * game. Students should develop their own implementation of
 * ::get_agent_info_at() and agent/world data structures.
 * */
typedef struct {
    AGENT_TYPE type;        /**< Agent type.        */
    unsigned char playable; /**< Is agent playable? */
    unsigned short id;      /**< Agent ID.          */
} AGENT;

/**
 * Structure defining world properties.
 *
 * @note This is an example which will probably not work in a fully functional
 * game. Students should develop their own implementation of
 * ::get_agent_info_at() and agent/world data structures.
 * */
 typedef struct {
    AGENT *grid;        /**< World is a grid composed of agents. */
    unsigned int xsize; /**< Horizontal world size.              */
    unsigned int ysize; /**< Vertical world size.                */
} WORLD;

/*typedef struct {
    AGENT **grid;        /**< World is a grid composed of agents. */
   /* unsigned int xsize; /**< Horizontal world size.              */
   /* unsigned int ysize; /**< Vertical world size.                */
/*} WORLD;*/

/* This function is an implementation of the definition provided by the
 * ::get_agent_info_at() function pointer. It only works for AGENT and WORLD
 * example structures defined in this file. */
unsigned int example_get_ag_info(void *world, unsigned int x, unsigned int y);

/**
 * This `main` function is only an example of: a) how to use the API defined in
 * the showworld.h header (mandatory for the project); and, b) how to use the
 * concrete simple implementation of the API (provided in the
 * showworld_simple.c file).
 *
 * @return Always zero.
 * */
int main() {

	/* An instance of a WORLD structure. */
    WORLD my_world;

    /* An instance of a SHOWWORLD world display. */
    SHOWWORLD *sw = NULL;

    /* A by-dimensional array of agents, representing agents in a grid. */
    AGENT agent_grid[WORLD_X][WORLD_Y];

    /* Number of agents created so far. */
    unsigned int nagents = 0;

    /* Initialize world display. */
    sw = showworld_new(WORLD_X, WORLD_Y, example_get_ag_info);

    /* Number of agents created so far. 
    unsigned int nagents = 0;
    unsigned int nhumanos = 0;
    unsigned int nzombies = 0;
    unsigned int nzplayers = 0;
    unsigned int nhplayers = 0;*/

    /* Initialize world display. */
    //sw = showworld_new(my_world->xsize, my_world->ysize, example_get_ag_info);

    /* Initialize random number generator. */
    srand(time(NULL));
    
    /*ini_sget(jogo_config,"mundo","xdim","%d",&my_world->xsize);
    ini_sget(jogo_config,"mundo","ydim","%d",&my_world->ysize);
    ini_sget(jogo_config,"agentes","nzombies","%d",&nzombies);
    ini_sget(jogo_config,"agentes","nhumanos","%d",&nhumanos);
	ini_sget(jogo_config,"agentes","nzplayers","%d",&nzplayers);
    ini_sget(jogo_config,"agentes","nhplayers","%d",&nhplayers);*/
    
    /*my_world->grid = (AGENT**)malloc(my_world->xsize*sizeof(AGENT));
    for(unsigned int i =0;i < my_world->xsize;i++){
		my_world->grid[i]=(AGENT*)malloc(my_world->ysize*sizeof(AGENT));
	}*/
	
   // unsigned int random1, random2;
    // unsigned int nAgentsColocar = nhumanos + nzombies;
    
    /* **************************************************************** */
    /* Cycle through all cells in grid and randomly place agents in it. */
    /* **************************************************************** */

    for (int i = 0; i < WORLD_X; ++i) {
        for (int j = 0; j < WORLD_Y; ++j) {

            /* Possible agent in grid. By default we assume there is none. */
            AGENT ag = {None, 0, 0};

            /* Obtain a probability between 0 and 99. */
            unsigned char probability = rand() % 100;

            /* There is 10% probability of creating an agent. */
            if (probability < 10) {

                /* If we got here, an agent will be placed at (i,j). */

                /* Randomly define agent type. */
                ag.type = (rand() % 2 == 0) ? Human : Zombie;

                /* Give 10% probablity of agent being playable by user. */
                ag.playable = (rand() % 10 == 0);

                /* Assign agent ID and then increment number of agents so
                   far. */
                ag.id = nagents++;

            }

            /* Assign possible agent to grid at (i,j). */
            agent_grid[i][j] = ag;
        }
    }
	/* for (unsigned int i = 0; i < my_world->xsize; ++i) {
      for (unsigned int j = 0; j < my_world->ysize; ++j) {
		  
         /* Possible agent in grid. By default we assume there is none. */
         
          /*AGENT ag = { None, 0, 0};
            do{
              AGENT  ag = { None, 0, 0};
                if (nhumanos > 0)
                {
                    random1 = rand() % my_world->xsize;
                    random2 = rand() % my_world->ysize;
                    if (my_world->grid[random1][random2].type != Zombie && my_world->grid[random1][random2].type != Human)
                    {
                        my_world->grid[random1][random2].type = Human;
                        if (nhplayers > 0)
                        {
                            my_world->grid[random1][random2].playable = 1;
                            nhplayers--;
                        }
                        else
                            my_world->grid[random1][random2].playable = 0;
                        nhumanos--;
                        nAgentsColocar--;
                        my_world->grid[random1][random2].id = nagents++;
                    }
                }
else if (nzombies > 0)
                {
                    random1 = rand() % my_world->xsize;
                    random2 = rand() % my_world->ysize;
                    if (my_world->grid[random1][random2].type != Zombie && my_world->grid[random1][random2].type != Human)
                    {
                        my_world->grid[random1][random2].type = Zombie;
                        if (nzplayers > 0)
                        {
                            my_world->grid[random1][random2].playable = 1;
                            nzplayers--;
                        }
                        else
                            my_world->grid[random1][random2].playable = 0;
                        nzombies--;
                        nAgentsColocar--;
                        my_world->grid[random1][random2].id = nagents++;
                    }
                }
            } while (nAgentsColocar > 0);
            /* Give 10% probablity of agent being playable by user. /


            / Assign possible agent to grid at (i,j). */
       /* }
    }

    for (int i = 0; i < my_world->xsize; i++)
    {
        for (int j = 0; j < my_world->ysize; j++)
        {
            if (my_world->grid[i][j].type != Zombie && my_world->grid[i][j].type != Human)
                my_world->grid[i][j] = { None, 0, 0};
        }
    }

    if (nhplayers > 0 || nzplayers > 0)
    {
        for (int i = 0; i < my_world->xsize; i++)
        {
            for (int j = 0; j < my_world->ysize; j++)
            {
                if (my_world->grid[i][j].type == Human && nhplayers > 0)
                {
                    my_world->grid[i][j].playable = 1;
                    nhplayers--;
                }
                else if (my_world->grid[i][j].type == Zombie && nzplayers > 0) {
                    my_world->grid[i][j].playable = 1;
                    nzplayers--;
                }
           }
        }
    }*/


	/*for (int i = 0; i < WORLD_X; ++i) {
        for (int j = 0; j < WORLD_Y; ++j) {
			if (ag.type =! None){
			ag_info = agents;	
			}
		}
	}*/
	
    /* ******************************* */
    /* Populate the my_world variable. */
    /* ******************************* */

/* A bidimensional array of agents can be interpreted as a pointer to
       agents. */
    my_world.grid = (AGENT *) agent_grid;

    /* World size is defined by constants in this example. */
    my_world.xsize = WORLD_X;
    my_world.ysize = WORLD_Y;
    
    /* A bidimensional array of agents can be interpreted as a pointer to
       agents. */
    //my_world->grid = (AGENT **) agent_grid;

    /* World size is defined by constants in this example. */
    //my_world.xsize = WORLD_X;
    //my_world.ysize = WORLD_Y;

    /* ********************************************************************* */
    /* Show world using the simple_show_world() function. This function can  */
    /* be used in the first part of the project.                             */
    /* ********************************************************************* */
    showworld_update(sw, &my_world);

    /* Before finishing, ask user to press ENTER. */
    printf("Press ENTER to continue...");
    getchar();

    /* Destroy world display. */
    showworld_destroy(sw);

    /* Bye. */
    return 0;
}

/**
 * This function is an implementation of the ::get_agent_info_at() function
 * definition. It only works for ::AGENT and ::WORLD structures defined in this
 * example.
 *
 * It basically receives a pointer to a ::WORLD structure, obtains the AGENT
 * structure in the given coordinates, and returns the agent information in a
 * bit-packed `unsigned int`.
 *
 * @note This is an example which will probably not work in a fully functional
 * game. Students should develop their own implementation of
 * ::get_agent_info_at() and agent/world data structures.
 *
 * @param w Generic pointer to object representing the simulation world.
 * @param x Horizontal coordinate of the simulation world from where to fetch
 * the agent information.
 * @param y Vertical coordinate of the simulation world from where to fetch
 * the agent information.
 * @return An integer containing bit-packed information about an agent, as
 * follows: bits 0-1 (agent type), bit 2 (is agent playable), bits 3-18 (agent
 * ID). Bits 19-31 are available for student-defined agent extensions.
 * */
unsigned int example_get_ag_info(void *w, unsigned int x, unsigned int y) {
		
		/* The agent information to return. */
    unsigned int ag_info = 0;

    /* Convert generic pointer to world to a WORLD object. */
    WORLD *my_world = (WORLD *) w;

    /* Check if the given (x,y) coordinates are within bounds of the world. */
    if ((x >= my_world->xsize) || (y >= my_world->ysize)) {

        /* If we got here, then the coordinates are off bounds. As such we will
           report that the requested agent is of unknown type. No need to
           specify agent ID or playable status, since the agent is unknown. */
        ag_info = Unknown;

    } else {

        /* Given coordinates are within bounds, let's get and pack the request
           agent information. */

        /* Obtain agent at specified coordinates. */
        AGENT ag = my_world->grid[x * my_world->ysize + y];

        /* Is there an agent at (x,y)? */
        if (ag.type == None) {

            /* If there is no agent at the (x,y) coordinates, set agent type to
               None. No need to specify agent ID or playable status, since
               there is no agent here. */
            ag_info = None;

        } else {

            /* If we get here it's because there is an agent at (x,y). Bit-pack
               all the agent information as specified by the get_agent_info_at
               function pointer definition. */
            ag_info = (ag.id << 3) | (ag.playable << 2) | ag.type;

        }

    }

    /* The agent information to return. */
    //unsigned int ag_info = 0;

    /* Convert generic pointer to world to a WORLD object. */
    //WORLD *my_world = (WORLD *) w;

    /* Check if the given (x,y) coordinates are within bounds of the world. */
   // if ((x >= my_world->xsize) || (y >= my_world->ysize)) {

        /* If we got here, then the coordinates are off bounds. As such we will
           report that the requested agent is of unknown type. No need to
           specify agent ID or playable status, since the agent is unknown. */
        //ag_info = Unknown;

   // } else {

        /* Given coordinates are within bounds, let's get and pack the request
           agent information. */

        /* Obtain agent at specified coordinates. */
       // AGENT ag = *my_world->grid[x * my_world->ysize + y];

        /* Is there an agent at (x,y)? */
       // if (ag.type == None) {

            /* If there is no agent at the (x,y) coordinates, set agent type to
               None. No need to specify agent ID or playable status, since
               there is no agent here. */
            //ag_info = None;

        //} else {

            /* If we get here it's because there is an agent at (x,y). Bit-pack
               all the agent information as specified by the get_agent_info_at
               function pointer definition. */
          //  ag_info = (ag.id << 3) | (ag.playable << 2) | ag.type;

      //  }

    //}

    /* Return the requested agent information. */
    return ag_info;
}
