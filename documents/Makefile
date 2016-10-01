#
##
### Makefile for YUML diagrams generation from text files to png/jpg/svg/pdf

#
## Include YUML Makefile rules
include yuml.mk

#
## Command line tools
RM =	rm -f


#
## Diagrams location
CLASS_FOLDER = class_diagram


#
## Class, activity and use case diagrams source files (txt)
CLASS_SRCS = $(CLASS_FOLDER)/software_diagram.class.yuml.txt

# ACTIVITY_SRCS = $(FOLDER)/example-diagram.activity.yuml.txt

# USECASE_SRCS = $(FOLDER)/example-diagram.usecase.yuml.txt


#
## YUML flags to adjust the desired outputs
##
## verbose: -v
## note: log output
##
## styles: -s (plain || nofunky || scruffy)
## note: diagram output; default is scruffy
##
## scale: --scale N
## note: diagram output; where N is a number representing a percentage;
##       this precentage representing the scale of the outputed diagram
##       in term of image resolution
YUML_FLAGS =	-v -s plain --scale 200


#
## Desired output format(s)
## Replace `PNG` by the desired output format
## Or add multiple output formats if you want more
## e.g.: $(YUML_PNGS) $(YUML_JPGS) $(YUML_SVGS) $(YUML_PDFS)
YUML_OUTPUT =	$(YUML_PNGS)


#
## Callable rules
##
## Will convert every source file to the desired output format(s)
all:		$(YUML_OUTPUT)

#
## Will delete every outputed file
clean:
		$(RM) $(YUML_OUTPUT)

#
## Same as clean; for convenience only
fclean:		clean

#
## Will delete every outputed file then regenerate them
re:		fclean all

.PHONY:		all clean fclean re
