#!/bin/bash

path="docs/class_diagram.puml"

if command -v hpp2plantuml >/dev/null; then
  hpp2plantuml -i "include/*/*.hpp" -i "include/*/*/*.hpp" -o $path && echo "UML diagram created in $path"
else
  echo "Skipping class diagram generation - hpp2plantuml not found"
fi
