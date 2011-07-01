#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>
#include <lines.hpp>
#include <name.hpp>

int IDAP_init(void)
{
	if(inf.filetype != f_ELF && inf.filetype != f_PE)    {
		error("Executable format must be PE or ELF, sorry.");
		return PLUGIN_SKIP;
	}

	return PLUGIN_KEEP;

}

void IDAP_term(void)
{
	return;
}

void IDAP_run(int arg)
{
	// The functions we're interested in.
	char *funcs[] = { "sprintf", "strcpy", "sscanf", "HeapCreate" , "HeapAlloc", "HeapReAlloc", "HeapFree", "LocalAlloc", "LocalFree",  0 };
	FILE *f;
	char filename[] = "import.txt";
	f = qfopen(filename, "wb");
	// Loop through all segments
	for (int i = 0; i < get_segm_qty(); i++) {
		segment_t *seg = getnseg(i);

		// We are only interested in the pseudo segment created by
		// IDA, which is of type SEG_XTRN. This segment holds all
		// function 'extern' definitions.
		if (seg->type == SEG_XTRN) {

			// Loop through each of the functions we're interested in.
			for (int i = 0; funcs[i] != 0; i++) {
				// Get the address of the function by its name
				ea_t loc = get_name_ea(seg->startEA, funcs[i]);
				// If the function was found, loop through it's
				// referrers.
				if (loc != BADADDR) {
					msg("Finding callers to %s (%a)\n", funcs[i], loc);
					xrefblk_t xb;
					// Loop through all the TO xrefs to our function.
					//for (bool ok = xb.first_to(loc, XREF_DATA); ok; ok = xb.next_to()) {
					for (bool ok = xb.first_to(loc, XREF_ALL); ok; ok = xb.next_to()) {
						// Get the instruction (as text) at that address.
						char instr[MAXSTR];
						char instr_clean[MAXSTR];
						generate_disasm_line(xb.from, instr, sizeof(instr)-1);
						// Remove the colour coding and format characters
						tag_remove(instr, instr_clean, sizeof(instr_clean)-1);
						//msg("Caller to %s: %a [%s]\n", funcs[i], xb.from, instr_clean);
						qfprintf(f,"Caller to %s: %a [%s]\n", funcs[i], xb.from, instr_clean);
	
					}
				}
				else{
					msg("failed to get address of function %s by its name\n", funcs[i]);
				}
			}
		}
	}
	qfclose( f );
	return;

}

char IDAP_comment[] = "Insecure Function Finder";
char IDAP_help[] = "Searches for all instances of strcpy(), sprintf() and sscanf().\n";


char IDAP_name[] = "Insecure Function Finder";
char IDAP_hotkey[] = "Alt-I";

plugin_t PLUGIN =
{
  IDP_INTERFACE_VERSION,
  0,
  IDAP_init,
  IDAP_term,
  IDAP_run,
  IDAP_comment,
  IDAP_help,
  IDAP_name,
  IDAP_hotkey
}; 