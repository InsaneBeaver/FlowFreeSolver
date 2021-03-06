#include "eval.h"

NodeEval::NodeEval(square_color** _analysisgridpointer, coordinate *** _sources, square_color _number_of_colors, coordinate _size) : 
	analysisgridpointer(_analysisgridpointer), sources(_sources), number_of_colors(_number_of_colors), size(_size)
{
	distances = new coordinate[number_of_colors];
	for(square_color i = 0; i < number_of_colors; i++)
		distances[i] = getdistance(sources[i][0][0], sources[i][0][1], sources[i][1][0], sources[i][1][1]);
}

int NodeEval::evaluateNode(Node * node)
{
	int evaluation = 0;
	if(node->lastnodeinpipe != NULL)
	{
		if(node->depth + 1 == size * size)
			evaluation = EVAL_SOLVED;
		
		else
		{
			evaluation = node->predecessor->eval + 50;
			square_color color = node->color;
			coordinate x = node->x;
			coordinate y = node->y;
			if(x == sources[color-1][1][0] && y == sources[color-1][1][1]) evaluation += 1000;
			else
			{
				coordinate distance = getdistance(x, y, sources[color - 1][1][0], sources[color - 1][1][1]);
				
				double powval = pow(3, -10 * (distance - distances[color - 1]));
				evaluation += 50 * (powval / (1 + powval) - 1);
				
				if(getdistance(node, node->lastnodeinpipe) < distance)
					evaluation += 100;
				
				
				if(node->lastnodeinpipe->lastnodeinpipe != NULL)
				{
					if(abs(x - node->lastnodeinpipe->lastnodeinpipe->x) == 2 || abs(y - node->lastnodeinpipe->lastnodeinpipe->y) == 2)
						evaluation += 100;
				}	
			
			}
			evaluation = min(evaluation, EVAL_NORMALMAX); // EVAL_SOLVED should be the highest possible eval as solved nodes are obviously the most important nodes
		}
		
	}
	return evaluation;
	
	
}
