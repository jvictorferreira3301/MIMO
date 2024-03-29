#!/bin/bash

echo "Atualizando listas de pacotes..."
sudo apt-get update

echo "Instalando make..."
sudo apt-get install -y make

echo "Instalando GSL..."
sudo apt-get install -y libgsl-dev

echo "Todas as dependências foram instaladas."
