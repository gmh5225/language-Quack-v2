; ModuleID = 'module'
source_filename = "module"

define dso_local i32 @main() {
main:
  %0 = alloca double, align 8
  store double 1.090000e+01, double* %0, align 8
  %1 = alloca double, align 8
  store double 1.080000e+01, double* %1, align 8
  %2 = icmp slt double* %0, %1
  ret i32 0
}
