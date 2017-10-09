#!/bin/bash

#scrip to test kernel headers installation

unamestr=$(uname -r)

ls  /lib/modules/"$unamestr"/build/

