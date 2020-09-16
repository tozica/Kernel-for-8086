/*
 * main.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: OS1
 */

#include "interr.h"


void userMain(int argc, char **argv);

int main(int argc, char **argv) {
	inic();

	userMain(argc, argv);

	restore();
}

