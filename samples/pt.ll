; ModuleID = '../samples/pt.qk'
source_filename = "../samples/pt.qk"

%Object_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Object*)*, void (%Object*)* }
%Object = type { %Object_vtable* }
%String = type { %String_vtable*, i8* }
%String_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%String*)*, void (%String*)*, i8 (%String*, %String*)*, i8 (%String*, %String*)*, %String* (%String*, %String*)* }
%Pt_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Object*)*, void (%Object*)*, i64 (%Pt*)*, i64 (%Pt*)* }
%Pt = type { %Pt_vtable*, i64, i64 }
%Nothing = type { %Nothing_vtable* }
%Nothing_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Nothing*)*, void (%Nothing*)*, i8 (%Nothing*, %Nothing*)*, i8 (%Nothing*, %Nothing*)* }

@ObjectVtable = external global %Object_vtable
@PtVtable = internal constant %Pt_vtable { %Object_vtable* @ObjectVtable, i8 (%Object*, %Object*)* @Object__eq__Object, i8 (%Object*, %Object*)* @Object__ne__Object, %String* (%Object*)* @Object__str__, void (%Object*)* @Object__del__, i64 (%Pt*)* @PtgetX, i64 (%Pt*)* @PtgetY }
@0 = private unnamed_addr constant [10 x i8] c"%ld %ld \0A\00", align 1

declare %Object* @Object_create()

declare %String* @String_create(i8*)

declare %Nothing* @Nothing_create()

define dso_local %Pt* @Pt_create(i64 %0, i64 %1) {
Pt_create:
  %2 = call i8* @malloc(i64 24)
  %3 = bitcast i8* %2 to %Pt*
  %4 = getelementptr inbounds %Pt, %Pt* %3, i32 0, i32 0
  store %Pt_vtable* @PtVtable, %Pt_vtable** %4
  call void @Pt_init(%Pt* %3, i64 %0, i64 %1)
  ret %Pt* %3
}

declare %Pt* @Object_init(%Pt*, i64, i64)

define dso_local void @Pt_init(%Pt* %0, i64 %1, i64 %2) {
Pt_init:
  %3 = alloca %Pt*
  store %Pt* %0, %Pt** %3
  %4 = alloca i64
  store i64 %1, i64* %4
  %5 = alloca i64
  store i64 %2, i64* %5
  %6 = load i64, i64* %4, align 8
  %7 = load %Pt*, %Pt** %3, align 8
  %8 = getelementptr inbounds %Pt, %Pt* %7, i32 0, i32 1
  store i64 %6, i64* %8
  %9 = load i64, i64* %5, align 8
  %10 = load %Pt*, %Pt** %3, align 8
  %11 = getelementptr inbounds %Pt, %Pt* %10, i32 0, i32 2
  store i64 %9, i64* %11
  ret void
}

declare i8* @malloc(i64)

declare void @Object__del__(%Object*)

declare %String* @Object__str__(%Object*)

declare i8 @Object__ne__Object(%Object*, %Object*)

define i64 @PtgetX(%Pt* %0) {
PtgetX:
  %1 = alloca %Pt*
  store %Pt* %0, %Pt** %1
  %2 = load %Pt*, %Pt** %1, align 8
  %3 = getelementptr inbounds %Pt, %Pt* %2, i32 0, i32 1
  %4 = load i64, i64* %3
  ret i64 %4
}

declare i8 @Object__eq__Object(%Object*, %Object*)

define i64 @PtgetY(%Pt* %0) {
PtgetY:
  %1 = alloca %Pt*
  store %Pt* %0, %Pt** %1
  %2 = load %Pt*, %Pt** %1, align 8
  %3 = getelementptr inbounds %Pt, %Pt* %2, i32 0, i32 2
  %4 = load i64, i64* %3
  ret i64 %4
}

define dso_local i64 @main() {
main:
  %0 = alloca i64, align 8
  store i64 1, i64* %0, align 8
  %1 = load i64, i64* %0, align 8
  %2 = alloca i64, align 8
  store i64 2, i64* %2, align 8
  %3 = load i64, i64* %2, align 8
  %4 = call %Pt* @Pt_create(i64 %1, i64 %3)
  %5 = alloca %Pt*, align 8
  store %Pt* %4, %Pt** %5, align 8
  %6 = load %Pt*, %Pt** %5, align 8
  %7 = getelementptr inbounds %Pt, %Pt* %6, i32 0, i32 0
  %8 = load %Pt_vtable*, %Pt_vtable** %7
  %9 = getelementptr inbounds %Pt_vtable, %Pt_vtable* %8, i32 0, i32 5
  %10 = load i64 (%Pt*)*, i64 (%Pt*)** %9
  %11 = call i64 %10(%Pt* %6)
  %12 = load %Pt*, %Pt** %5, align 8
  %13 = getelementptr inbounds %Pt, %Pt* %12, i32 0, i32 0
  %14 = load %Pt_vtable*, %Pt_vtable** %13
  %15 = getelementptr inbounds %Pt_vtable, %Pt_vtable* %14, i32 0, i32 6
  %16 = load i64 (%Pt*)*, i64 (%Pt*)** %15
  %17 = call i64 %16(%Pt* %12)
  %18 = call i32 (...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @0, i32 0, i32 0), i64 %11, i64 %17)
  ret i64 0
}

declare i32 @printf(...)
