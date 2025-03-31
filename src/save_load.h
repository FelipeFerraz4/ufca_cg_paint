#ifndef SAVE_LOAD_H  // Evita múltiplas inclusões
#define SAVE_LOAD_H
#include <vector>
#include "primary_objects.h"
#include "estruturas.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include "save_load.h"

void save_objects(draws &structure_list);
void load_objects(draws &structure_list);

#endif
