ramstage-y += haswell_init.c
subdirs-y += ../../x86/name
ramstage-y += mp_init.c
romstage-y += romstage.c

ramstage-$(CONFIG_GENERATE_ACPI_TABLES) += acpi.c
ramstage-$(CONFIG_HAVE_SMI_HANDLER) += smmrelocate.c

cpu_microcode-$(CONFIG_CPU_MICROCODE_CBFS_GENERATE)  += microcode_blob.c

smm-$(CONFIG_HAVE_SMI_HANDLER) += finalize.c

cpu_incs += $(src)/cpu/intel/haswell/cache_as_ram.inc

# AP startub stub
SIPI_ELF=$(obj)/cpu/intel/haswell/sipi_vector.elf
SIPI_BIN=$(SIPI_ELF:.elf=)
SIPI_DOTO=$(SIPI_ELF:.elf=.o)

ramstage-srcs += $(SIPI_BIN)
rmodules-y += sipi_vector.S
rmodules-y += sipi_header.c

$(SIPI_DOTO): $(dir $(SIPI_ELF))sipi_vector.rmodules.o $(dir $(SIPI_ELF))sipi_header.rmodules.o
	$(CC) $(LDFLAGS) -nostdlib -r -o $@ $^

$(eval $(call rmodule_link,$(SIPI_ELF), $(SIPI_ELF:.elf=.o), 0))

$(SIPI_BIN): $(SIPI_ELF)
	$(OBJCOPY) -O binary $< $@

$(SIPI_BIN).ramstage.o: $(SIPI_BIN)
	@printf "    OBJCOPY    $(subst $(obj)/,,$(@))\n"
	cd $(dir $@); $(OBJCOPY) -I binary $(notdir $<) -O elf32-i386 -B i386 $(notdir $@)

