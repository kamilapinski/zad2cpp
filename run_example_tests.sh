#!/bin/bash

make
./strqueue_test_1_dbg 2> tmp.log
diff -B tmp.log strqueue_test_1.log

./strqueue_test_1_nodbg 2> tmp.log

./strqueue_test_2_dbg_a 2> tmp.log
diff -B tmp.log strqueue_test_2.log

./strqueue_test_2_dbg_b 2> tmp.log
diff -B tmp.log strqueue_test_2.log

./strqueue_test_2_nodbg 2> tmp.log

make clean