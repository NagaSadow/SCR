#!/bin/bash

tar -cvf "$3".tar $(find *."$1" -mtime -"$2")
