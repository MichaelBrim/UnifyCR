/*
 * Copyright (c) 2020, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 *
 * Copyright 2020, UT-Battelle, LLC.
 *
 * LLNL-CODE-741539
 * All rights reserved.
 *
 * This is the license for UnifyFS.
 * For details, see https://github.com/LLNL/UnifyFS.
 * Please read https://github.com/LLNL/UnifyFS/LICENSE for full license text.
 */

#include "testutil.h"

/* -------- Main Program -------- */

/* Description:
 *
 * [ Mode 1: N-to-1 shared-file ]
 *    Each rank calls stat() on the shared file, and the file size is checked
 *    to verify it is identical across all clients.
 *
 * [ Mode 2: N-to-N file-per-process ]
 *    Each rank calls stat() on its per-process file. If cfg.io_shuffle is
 *    enabled, the rank space is inverted for determining which file to stat().
 */

int main(int argc, char* argv[])
{
    char* target_file;
    int rc;

    test_cfg test_config;
    test_cfg* cfg = &test_config;
    test_timer time_stat;

    timer_init(&time_stat, "stat");

    rc = test_init(argc, argv, cfg);
    if (rc) {
        fprintf(stderr, "ERROR - Test %s initialization failed!",
                argv[0]);
        fflush(NULL);
        return rc;
    }

    if (!test_config.use_mpi) {
        fprintf(stderr, "ERROR - Test %s requires MPI!",
                argv[0]);
        fflush(NULL);
        return -1;
    }

    if ((test_config.io_pattern == IO_PATTERN_NN) && test_config.io_shuffle) {
        test_config.rank = (test_config.n_ranks - 1) - test_config.rank;
    }

    // create file
    target_file = test_target_filename(cfg);
    test_print_verbose_once(cfg, "DEBUG: target file %s",
                            target_file);

    // file stat check
    timer_start_barrier(cfg, &time_stat);
    rc = stat_cmd(cfg, target_file);
    timer_stop_barrier(cfg, &time_stat);
    if (rc) {
        test_print(cfg, "ERROR - stat(%s) failed", target_file);
    }
    test_print_verbose_once(cfg, "DEBUG: finished stat");

    test_print_once(cfg, "\nFile stat time: %.6lf sec\n",
                    time_stat.elapsed_sec_all);


    // cleanup
    free(target_file);

    timer_fini(&time_stat);

    test_fini(cfg);

    return 0;
}
