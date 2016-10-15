#
##
### Makefile for YUML diagrams generation from text files to png/jpg/svg/pdf
##
# MIT License

# Copyright (c) 2016, Nicolas Chauvin

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#
## Command line tools
YUML =	yuml

RM =	rm -f


#
## Rules that convert the source files to the desired format (png, jpg, svg, pdf)
YUML_PNGS = 	$(CLASS_SRCS:.class.yuml.txt=.class.yuml.png) \
		$(ACTIVITY_SRCS:.activity.yuml.txt=.activity.yuml.png) \
		$(USECASE_SRCS:.usecase.yuml.txt=.usecase.yuml.png)

YUML_JPGS = 	$(CLASS_SRCS:.class.yuml.txt=.class.yuml.jpg) \
		$(ACTIVITY_SRCS:.activity.yuml.txt=.activity.yuml.jpg) \
		$(USECASE_SRCS:.usecase.yuml.txt=.usecase.yuml.jpg)

YUML_SVGS = 	$(CLASS_SRCS:.class.yuml.txt=.class.yuml.svg) \
		$(ACTIVITY_SRCS:.activity.yuml.txt=.activity.yuml.svg) \
		$(USECASE_SRCS:.usecase.yuml.txt=.usecase.yuml.svg)

YUML_PDFS = 	$(CLASS_SRCS:.class.yuml.txt=.class.yuml.pdf) \
		$(ACTIVITY_SRCS:.activity.yuml.txt=.activity.yuml.pdf) \
		$(USECASE_SRCS:.usecase.yuml.txt=.usecase.yuml.pdf)


#
## Makefile rules to convert .txt files to the desired output(s)
##
## .txt to .png
%.class.yuml.png:	%.class.yuml.txt
		$(YUML) -i $< -o $@ -f png -t class $(YUML_FLAGS)

%.activity.yuml.png:	%.activity.yuml.txt
		$(YUML) -i $< -o $@ -f png -t activity $(YUML_FLAGS)

%.usecase.yuml.png:	%.usecase.yuml.txt
		$(YUML) -i $< -o $@ -f png -t usecase $(YUML_FLAGS)

#
## .txt to .jpg
%.class.yuml.jpg:	%.class.yuml.txt
		$(YUML) -i $< -o $@ -f jpg -t class $(YUML_FLAGS)

%.activity.yuml.jpg:	%.activity.yuml.txt
		$(YUML) -i $< -o $@ -f jpg -t activity $(YUML_FLAGS)

%.usecase.yuml.jpg:	%.usecase.yuml.txt
		$(YUML) -i $< -o $@ -f jpg -t usecase $(YUML_FLAGS)

#
## .txt to .svg
%.class.yuml.svg:	%.class.yuml.txt
		$(YUML) -i $< -o $@ -f svg -t class $(YUML_FLAGS)

%.activity.yuml.svg:	%.activity.yuml.txt
		$(YUML) -i $< -o $@ -f svg -t activity $(YUML_FLAGS)

%.usecase.yuml.svg:	%.usecase.yuml.txt
		$(YUML) -i $< -o $@ -f svg -t usecase $(YUML_FLAGS)

#
## .txt to .pdf
%.class.yuml.pdf:	%.class.yuml.txt
		$(YUML) -i $< -o $@ -f pdf -t class $(YUML_FLAGS)

%.activity.yuml.pdf:	%.activity.yuml.txt
		$(YUML) -i $< -o $@ -f pdf -t activity $(YUML_FLAGS)

%.usecase.yuml.pdf:	%.usecase.yuml.txt
		$(YUML) -i $< -o $@ -f pdf -t usecase $(YUML_FLAGS)
