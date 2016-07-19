############################# Makefile ##########################
#                 Projeto: XXXXXX                               #
#                 Arquivo: Makefile (example_cgi.cgi)           #
#                 Data: 29/09/2011                              #
#                                                               #
#              Linear Equipamentos Eletronicos S/A              #
#################################################################

NAME = example_cgi.cgi
#Compiler
  CC = gcc
#Compiler options
  CFLAGS = -Wall
#Exec Name
EXEC = example_cgi SRC = $ (wildcard *.c) OBJ = $ (SRC:.c =.o)
#Nome do arquivo binario que será criado "Nome do Programa"
all: $ (EXEC) @ echo "Compilando " $ (NAME) example_cgi: $ (OBJ) @ $ (CC) - o $ (NAME) $ ^.PHONY: clean mrproper clean:
@echo $ (NAME)
  @ echo "Limpando compilação...." @ rm - rf *.o
#Apaga tudo que deve ser modificado
mrproper:clean @ echo "Apagando arquivos" rm - rf $ (EXEC)
