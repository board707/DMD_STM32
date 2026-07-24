# Register-test profiles

Each chip subfolder contains generated register profiles split by scan rate.
Uncomment matching `*_scan_N.h` files in `register_test_config.h`; they are
combined in include order.

The interactive test and `DMD_SPWM_REGISTER_OVERRIDE` use the same profiles.
An override therefore requires the scan header containing that `regtypeN` to
remain uncommented. Missing register numbers produce a compile-time error.

