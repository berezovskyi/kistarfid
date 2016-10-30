NAME=final_report

.PHONY: all clean

all:
	xelatex $(NAME).tex
	bibtex $(NAME).aux
	xelatex $(NAME).tex
	xelatex $(NAME).tex

clean:
	$(RM) $(NAME).log $(NAME).lof $(NAME).out $(NAME).aux $(NAME).bbl $(NAME).blg $(NAME).toc $(NAME).pdf
