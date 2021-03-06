#include <stdio.h>
#include <string.h>
#include "acroform.h"
#include "auxiliary.h"
#include "catalog.h"
#include "cert.h"
#include "config.h"
#include "contents.h"
#include "cryptography.h"
#include "header.h"
#include "sig_dict.h"
#include "sig_field.h"
#include "sigil.h"
#include "trailer.h"
#include "xref.h"

static void print_usage(const char *prog)
{
    fprintf(stderr, " USAGE\n");
    fprintf(stderr, "     $ %s [OPTION]\n", prog);
    fprintf(stderr, " OPTIONS\n");
    fprintf(stderr, "     -q, --quiet\n");
    fprintf(stderr, "         do not print any output\n");
    fprintf(stderr, "     -v, --verbose\n");
    fprintf(stderr, "         provide more detailed output\n");
}

int main(int argc, char **argv)
{
    int verbosity = 1,
        failed    = 0;

    if (argc == 2) {
        if (strcmp(argv[1], "-q"     ) == 0 ||
            strcmp(argv[1], "--quiet") == 0)
        {
            verbosity = 0;
        } else if (strcmp(argv[1], "-v"       ) == 0 ||
                   strcmp(argv[1], "--verbose") == 0)
        {
            verbosity = 2;
        } else {
            print_usage(argv[0]);
            return 1;
        }
    } else if (argc > 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (verbosity >= 1)
        printf("\n ======= STARTING TEST PROCEDURE =======\n");

    // call self_test function for each module
    if (sigil_config_self_test(verbosity) != 0)
        failed++;
    if (sigil_auxiliary_self_test(verbosity) != 0)
        failed++;
    if (sigil_header_self_test(verbosity) != 0)
        failed++;
    if (sigil_trailer_self_test(verbosity) != 0)
        failed++;
    if (sigil_xref_self_test(verbosity) != 0)
        failed++;
    if (sigil_acroform_self_test(verbosity) != 0)
        failed++;
    if (sigil_catalog_self_test(verbosity) != 0)
        failed++;
    if (sigil_cert_self_test(verbosity) != 0)
        failed++;
    if (sigil_contents_self_test(verbosity) != 0)
        failed++;
    if (sigil_cryptography_self_test(verbosity) != 0)
        failed++;
    if (sigil_sig_dict_self_test(verbosity) != 0)
        failed++;
    if (sigil_sig_field_self_test(verbosity) != 0)
        failed++;
    if (sigil_sigil_self_test(verbosity) != 0)
        failed++;

    if (verbosity >= 1)
        printf("\n TOTAL FAILED: %d\n", failed);

    return (failed != 0);
}
