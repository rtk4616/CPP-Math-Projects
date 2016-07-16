#!/bin/sh
octave --no-gui -q simppenadj.m
gpicview simppenadj-standard-plot.png simppenadj-phase-plot.png
