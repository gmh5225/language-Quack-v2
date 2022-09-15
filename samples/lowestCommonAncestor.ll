; ModuleID = '../samples/lowestCommonAncestor.qk'
source_filename = "../samples/lowestCommonAncestor.qk"

%Object = type { %Object_vtable* }
%Object_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Object*)*, void (%Object*)* }
%String = type { %String_vtable*, i8* }
%String_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%String*)*, void (%String*)*, i8 (%String*, %String*)*, i8 (%String*, %String*)*, %String* (%String*, %String*)* }
%Nothing = type { %Nothing_vtable* }
%Nothing_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Nothing*)*, void (%Nothing*)*, i8 (%Nothing*, %Nothing*)*, i8 (%Nothing*, %Nothing*)* }

@0 = private unnamed_addr constant [7 x i8] c"String\00", align 1

declare %Object* @Object_create()

declare %String* @String_create(i8*)

declare %Nothing* @Nothing_create()

define dso_local i64 @main() {
main:
  %0 = alloca i64, align 8
  store i64 1, i64* %0, align 8
  %1 = load i64, i64* %0, align 8
  %2 = icmp eq i64 %1, 1
  br i1 %2, label %if.then, label %if.else

if.then:                                          ; preds = %main
  %3 = call %String* @String_create(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @0, i32 0, i32 0))
  %4 = alloca %String*, align 8
  store %String* %3, %String** %4, align 8
  %5 = bitcast %String** %4 to %Object**
  br label %if.cont

if.else:                                          ; preds = %main
  %6 = call %Nothing* @Nothing_create()
  %7 = alloca %Nothing*, align 8
  store %Nothing* %6, %Nothing** %7, align 8
  %8 = bitcast %Nothing** %7 to %Object**
  br label %if.cont

if.cont:                                          ; preds = %if.else, %if.then
  %9 = phi %Object** [ %8, %if.else ], [ %5, %if.then ]
  ret i64 0
}
