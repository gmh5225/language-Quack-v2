; ModuleID = '../samples/TypeCase.qk'
source_filename = "../samples/TypeCase.qk"

%Object = type { %Object_vtable* }
%Object_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Object*)*, void (%Object*)* }
%String = type { %String_vtable*, i8* }
%String_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%String*)*, void (%String*)*, i8 (%String*, %String*)*, i8 (%String*, %String*)*, %String* (%String*, %String*)* }
%Nothing = type { %Nothing_vtable* }
%Nothing_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Nothing*)*, void (%Nothing*)*, i8 (%Nothing*, %Nothing*)*, i8 (%Nothing*, %Nothing*)* }

@0 = private unnamed_addr constant [12 x i8] c"Hello World\00", align 1
@1 = private unnamed_addr constant [15 x i8] c"It is a string\00", align 1
@2 = private unnamed_addr constant [5 x i8] c"%s \0A\00", align 1
@3 = private unnamed_addr constant [5 x i8] c"%s \0A\00", align 1

declare %Object* @Object_create()

declare %String* @String_create(i8*)

declare %Nothing* @Nothing_create()

define dso_local i64 @main() {
main:
  %0 = call %String* @String_create(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @0, i32 0, i32 0))
  %1 = alloca %Object*, align 8
  store %String* %0, %Object** %1, align 8
  %2 = load %Object*, %Object** %1, align 8
  %3 = getelementptr inbounds %Object, %Object* %2, i32 0, i32 0
  %4 = load %Object_vtable*, %Object_vtable** %3
  %5 = call %String_vtable* @String_get_vtable()
  %6 = call i8 @is_subtype(%String_vtable* %5, %Object_vtable* %4)
  br i8 %6, label %typecase.if.String, label %typecase.not.String

typecase.if.String:                               ; preds = %main
  %7 = bitcast %Object* %2 to %String*
  %8 = alloca %String*
  store %String* %7, %String** %8
  %9 = call %String* @String_create(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @1, i32 0, i32 0))
  %10 = call i8* @String_getData(%String* %9)
  %11 = call i32 (...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @2, i32 0, i32 0), i8* %10)
  br label %typecase.not.String

typecase.not.String:                              ; preds = %typecase.if.String, %main
  %12 = call %Nothing_vtable* @Nothing_get_vtable()
  %13 = call i8 @is_subtype(%Nothing_vtable* %12, %Object_vtable* %4)
  br i8 %13, label %typecase.if.Nothing, label %typecase.not.Nothing

typecase.if.Nothing:                              ; preds = %typecase.not.String
  %14 = bitcast %Object* %2 to %Nothing*
  %15 = alloca %Nothing*
  store %Nothing* %14, %Nothing** %15
  %16 = call %Nothing* @Nothing_create()
  %17 = getelementptr inbounds %Nothing, %Nothing* %16, i32 0, i32 0
  %18 = load %Nothing_vtable*, %Nothing_vtable** %17
  %19 = getelementptr inbounds %Nothing_vtable, %Nothing_vtable* %18, i32 0, i32 3
  %20 = load %String* (%Nothing*)*, %String* (%Nothing*)** %19
  %21 = call %String* %20(%Nothing* %16)
  %22 = call i8* @String_getData(%String* %21)
  %23 = call i32 (...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @3, i32 0, i32 0), i8* %22)
  br label %typecase.not.Nothing

typecase.not.Nothing:                             ; preds = %typecase.if.Nothing, %typecase.not.String
  ret i64 0
}

declare i8 @is_subtype(%Object_vtable*, %Object_vtable*)

declare %String_vtable* @String_get_vtable()

declare i32 @printf(...)

declare i8* @String_getData(%String*)

declare %Nothing_vtable* @Nothing_get_vtable()
