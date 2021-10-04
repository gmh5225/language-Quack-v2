; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.String = type { %struct.StringVTable*, i64, i8* }
%struct.StringVTable = type { i32 (%struct.String*, %struct.String*)*, %struct.Object* (...)*, void (%struct.Object*)* }
%struct.Object = type { %struct.ObjectVTable*, i64 }
%struct.ObjectVTable = type { i32 (%struct.Object*, %struct.Object*)*, %struct.Object* (%struct.Object*)*, void (%struct.Object*)* }

@.str = private unnamed_addr constant [12 x i8] c"hello world\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local i32 @main() #0 {
  %1 = alloca %struct.String*, align 8
  %2 = call %struct.String* @newString(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i64 0, i64 0))
  store %struct.String* %2, %struct.String** %1, align 8
  %3 = load %struct.String*, %struct.String** %1, align 8
  %4 = getelementptr inbounds %struct.String, %struct.String* %3, i32 0, i32 0
  %5 = load %struct.StringVTable*, %struct.StringVTable** %4, align 8
  %6 = getelementptr inbounds %struct.StringVTable, %struct.StringVTable* %5, i32 0, i32 2
  %7 = load void (%struct.Object*)*, void (%struct.Object*)** %6, align 8
  %8 = load %struct.String*, %struct.String** %1, align 8
  %9 = bitcast %struct.String* %8 to %struct.Object*
  call void %7(%struct.Object* %9)
  ret i32 0
}

declare %struct.String* @newString(i8*) #1

attributes #0 = { noinline nounwind optnone ssp uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 12.0.0"}
