; ModuleID = 'test_quack_runtime.c'
source_filename = "test_quack_runtime.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.Integer = type { %struct.header, %struct.IntegerVTable*, i64 }
%struct.header = type { i64, i32 }
%struct.IntegerVTable = type { %struct.Boolean* (%struct.Integer*, %struct.Integer*)*, %struct.Nothing* (%struct.Integer*)*, %struct.Nothing* (%struct.Object*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)* }
%struct.Boolean = type { %struct.header, %struct.BooleanVTable*, i64 }
%struct.BooleanVTable = type { %struct.Boolean* (%struct.Boolean*, %struct.Boolean*)*, %struct.Nothing* (%struct.Boolean*)*, %struct.Nothing* (%struct.Boolean*)* }
%struct.Nothing = type { %struct.header, %struct.NothingVTable* }
%struct.NothingVTable = type { %struct.Boolean* (%struct.Nothing*, %struct.Nothing*)*, %struct.Nothing* (%struct.Nothing*)*, %struct.Nothing* (%struct.Nothing*)* }
%struct.Object = type { %struct.header, %struct.ObjectVTable* }
%struct.ObjectVTable = type { %struct.Boolean* (%struct.Object*, %struct.Object*)*, {}*, {}* }

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local void @testIntegerAddition() #0 {
  %1 = alloca %struct.Integer*, align 8
  %2 = alloca %struct.Integer*, align 8
  %3 = alloca %struct.Integer*, align 8
  %4 = call %struct.Integer* @newInteger(i64 1)
  store %struct.Integer* %4, %struct.Integer** %1, align 8
  %5 = call %struct.Integer* @newInteger(i64 2)
  store %struct.Integer* %5, %struct.Integer** %2, align 8
  %6 = load %struct.Integer*, %struct.Integer** %1, align 8
  %7 = getelementptr inbounds %struct.Integer, %struct.Integer* %6, i32 0, i32 1
  %8 = load %struct.IntegerVTable*, %struct.IntegerVTable** %7, align 8
  %9 = getelementptr inbounds %struct.IntegerVTable, %struct.IntegerVTable* %8, i32 0, i32 7
  %10 = load %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)** %9, align 8
  %11 = load %struct.Integer*, %struct.Integer** %1, align 8
  %12 = load %struct.Integer*, %struct.Integer** %2, align 8
  %13 = call %struct.Integer* %10(%struct.Integer* %11, %struct.Integer* %12)
  store %struct.Integer* %13, %struct.Integer** %3, align 8
  %14 = load %struct.Integer*, %struct.Integer** %3, align 8
  %15 = getelementptr inbounds %struct.Integer, %struct.Integer* %14, i32 0, i32 1
  %16 = load %struct.IntegerVTable*, %struct.IntegerVTable** %15, align 8
  %17 = getelementptr inbounds %struct.IntegerVTable, %struct.IntegerVTable* %16, i32 0, i32 1
  %18 = load %struct.Nothing* (%struct.Integer*)*, %struct.Nothing* (%struct.Integer*)** %17, align 8
  %19 = load %struct.Integer*, %struct.Integer** %3, align 8
  %20 = call %struct.Nothing* %18(%struct.Integer* %19)
  ret void
}

declare %struct.Integer* @newInteger(i64) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local i32 @main() #0 {
  call void @testIntegerAddition()
  ret i32 0
}

attributes #0 = { noinline nounwind optnone ssp uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 12.0.0"}
