CFLAGS += -Wall -g -O0
LDFLAGS += -lm -ldarnit

# Hidden directory for dependency files
DEPDIR = .deps
df = $(DEPDIR)/$(*F)

.PHONY: all clean

all: orientation.elf inventory.elf

clean:
	@echo " [ RM ] *.elf *.o"
	@$(RM) *.o *.elf
	@$(RM) -R $(DEPDIR)

orientation.elf: orientation.c.o tag.c.o trigonometry.c.o
	@echo " [ LD ] $(CURRENTPATH)$@"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

inventory.elf: inventory.c.o tag.c.o trigonometry.c.o
	@echo " [ LD ] $(CURRENTPATH)$@"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)



$(DEPDIR):
	@mkdir -p $@

# Compile C files
%.c.o: %.c | $(DEPDIR)
	@echo " [ CC ] $(CURRENTPATH)$<"
	@$(CC) -c $(CFLAGS) -MD -o $@ $<
	@cp $*.c.d $(df).c.P; sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $*.c.d >> $(df).c.P; $(RM) $*.c.d

# Compile ASM files with C pre-processor directives
%.S.o: %.S | $(DEPDIR)
	@echo " [ AS ] $(CURRENTPATH)$<"
	@$(CC) -c $(ASFLAGS) -MD -o $@ $<
	@cp $*.S.d $(df).S.P; sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $*.S.d >> $(df).S.P; $(RM) $*.S.d

# Link symbol lists to object files
%.syms.o: %.syms
	@$(LD) -o $@ -r --just-symbols=$<

# Check dependencies
-include $(CFILES:%.c=$(DEPDIR)/%.c.P)
-include $(ASMFILES:%.S=$(DEPDIR)/%.S.P)
