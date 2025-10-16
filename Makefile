CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g -I. -IConsignes -IUI -IShapes -IExport
OBJDIR = bin
BINDIR = bin

# Liste de tous les fichiers .c
SRCS = Consignes/utils.c \
       Export/export.c \
       UI/menu.c \
       UI/creation.c \
       UI/changement.c \
       Shapes/shapes.c 

# Corresponding object files
OBJS = $(SRCS:.c=.o)
OBJS := $(patsubst %,$(OBJDIR)/%,$(OBJS))

# Nom de l'exécutable
TARGET = $(BINDIR)/projet

# Création des dossiers bin et bin/Shapes etc. si manquants
$(shell mkdir -p $(OBJDIR)/UI $(OBJDIR)/Consignes $(OBJDIR)/Shapes $(OBJDIR)/Export)

# 👇 Ligne à bien mettre sans indentation !
build: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@



# Nettoyage
clean:
	rm -rf $(OBJDIR)/* $(TARGET)

.PHONY: all clean
