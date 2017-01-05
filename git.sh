#!/bin/sh
echo "# NeuralNetwork" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/mdlazreg/NeuralNetwork.git
git push -u origin master
