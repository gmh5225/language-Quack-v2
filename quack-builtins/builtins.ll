; ModuleID = 'builtins.c'
source_filename = "builtins.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.class_Obj_struct = type { %struct.class_Obj_struct*, {}*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Obj_struct*)* }
%struct.obj_Boolean_struct = type { %struct.class_Boolean_struct*, i32 }
%struct.class_Boolean_struct = type { %struct.class_Obj_struct*, %struct.obj_Boolean_struct* ()*, {}*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Boolean_struct*)* }
%struct.obj_String_struct = type { %struct.class_String_struct*, i8* }
%struct.class_String_struct = type { %struct.class_Obj_struct*, %struct.obj_String_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_String_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_String_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_String_struct*, %struct.obj_String_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_String_struct*, %struct.obj_String_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_String_struct*, %struct.obj_String_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_String_struct*, %struct.obj_String_struct*)*, %struct.obj_String_struct* (%struct.obj_String_struct*, %struct.obj_String_struct*)* }
%struct.obj_Obj_struct = type { %struct.class_Obj_struct* }
%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.__sFILEX = type opaque
%struct.__sbuf = type { i8*, i32 }
%struct.obj_Nothing_struct = type { %struct.class_Nothing_struct* }
%struct.class_Nothing_struct = type { %struct.class_Obj_struct*, {}*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Nothing_struct*)* }
%struct.class_Int_struct = type { %struct.class_Obj_struct*, {}*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* }
%struct.obj_Int_struct = type { %struct.class_Int_struct*, i32 }

@the_class_Obj = dso_local global %struct.class_Obj_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Obj_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Obj_struct*)* }* @the_class_Obj_struct to %struct.class_Obj_struct*), align 8
@.str = private unnamed_addr constant [17 x i8] c"<Object at %08x>\00", align 1
@__stdoutp = external global %struct.__sFILE*, align 8
@.str.1 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@lit_true = dso_local global %struct.obj_Boolean_struct* @lit_true_struct, align 8
@lit_false = dso_local global %struct.obj_Boolean_struct* @lit_false_struct, align 8
@the_class_Obj_struct = dso_local global { %struct.class_Obj_struct*, %struct.obj_Obj_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Obj_struct*)* } { %struct.class_Obj_struct* null, %struct.obj_Obj_struct* ()* @new_Obj, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)* @Obj_method_EQUALS, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)* @Obj_method_PRINT, %struct.obj_String_struct* (%struct.obj_Obj_struct*)* @Obj_method_STR }, align 8
@the_class_String = dso_local global %struct.class_String_struct* @the_class_String_struct, align 8
@.str.2 = private unnamed_addr constant [5 x i8] c"%s%s\00", align 1
@the_class_String_struct = dso_local global %struct.class_String_struct { %struct.class_Obj_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Obj_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Obj_struct*)* }* @the_class_Obj_struct to %struct.class_Obj_struct*), %struct.obj_String_struct* ()* @new_String, %struct.obj_Boolean_struct* (%struct.obj_String_struct*, %struct.obj_Obj_struct*)* @String_method_EQUALS, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)* @Obj_method_PRINT, %struct.obj_String_struct* (%struct.obj_String_struct*)* @String_method_STR, %struct.obj_Boolean_struct* (%struct.obj_String_struct*, %struct.obj_String_struct*)* @String_method_ATLEAST, %struct.obj_Boolean_struct* (%struct.obj_String_struct*, %struct.obj_String_struct*)* @String_method_ATMOST, %struct.obj_Boolean_struct* (%struct.obj_String_struct*, %struct.obj_String_struct*)* @String_method_LESS, %struct.obj_Boolean_struct* (%struct.obj_String_struct*, %struct.obj_String_struct*)* @String_method_MORE, %struct.obj_String_struct* (%struct.obj_String_struct*, %struct.obj_String_struct*)* @String_method_PLUS }, align 8
@the_class_Boolean = dso_local global %struct.class_Boolean_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Boolean_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Boolean_struct*)* }* @the_class_Boolean_struct to %struct.class_Boolean_struct*), align 8
@.str.3 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.str.4 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@__stderrp = external global %struct.__sFILE*, align 8
@.str.5 = private unnamed_addr constant [23 x i8] c"Unknown boolean object\00", align 1
@the_class_Boolean_struct = dso_local global { %struct.class_Obj_struct*, %struct.obj_Boolean_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Boolean_struct*)* } { %struct.class_Obj_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Obj_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Obj_struct*)* }* @the_class_Obj_struct to %struct.class_Obj_struct*), %struct.obj_Boolean_struct* ()* @new_Boolean, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)* @Obj_method_EQUALS, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)* @Obj_method_PRINT, %struct.obj_String_struct* (%struct.obj_Boolean_struct*)* @Boolean_method_STR }, align 8
@lit_false_struct = dso_local global %struct.obj_Boolean_struct { %struct.class_Boolean_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Boolean_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Boolean_struct*)* }* @the_class_Boolean_struct to %struct.class_Boolean_struct*), i32 0 }, align 8
@lit_true_struct = dso_local global %struct.obj_Boolean_struct { %struct.class_Boolean_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Boolean_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Boolean_struct*)* }* @the_class_Boolean_struct to %struct.class_Boolean_struct*), i32 1 }, align 8
@none = dso_local global %struct.obj_Nothing_struct* @nothing_struct, align 8
@.str.6 = private unnamed_addr constant [10 x i8] c"<nothing>\00", align 1
@the_class_Nothing_struct = dso_local global { %struct.class_Obj_struct*, %struct.obj_Nothing_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Nothing_struct*)* } { %struct.class_Obj_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Obj_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Obj_struct*)* }* @the_class_Obj_struct to %struct.class_Obj_struct*), %struct.obj_Nothing_struct* ()* @new_Nothing, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)* @Obj_method_EQUALS, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)* @Obj_method_PRINT, %struct.obj_String_struct* (%struct.obj_Nothing_struct*)* @Nothing_method_STR }, align 8
@the_class_Nothing = dso_local global %struct.class_Nothing_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Nothing_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Nothing_struct*)* }* @the_class_Nothing_struct to %struct.class_Nothing_struct*), align 8
@nothing_struct = dso_local global %struct.obj_Nothing_struct { %struct.class_Nothing_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Nothing_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Nothing_struct*)* }* @the_class_Nothing_struct to %struct.class_Nothing_struct*) }, align 8
@the_class_Int = dso_local global %struct.class_Int_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Int_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* }* @the_class_Int_struct to %struct.class_Int_struct*), align 8
@.str.7 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@the_class_Int_struct = dso_local global { %struct.class_Obj_struct*, %struct.obj_Int_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)*, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* } { %struct.class_Obj_struct* bitcast ({ %struct.class_Obj_struct*, %struct.obj_Obj_struct* ()*, %struct.obj_Boolean_struct* (%struct.obj_Obj_struct*, %struct.obj_Obj_struct*)*, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Obj_struct*)* }* @the_class_Obj_struct to %struct.class_Obj_struct*), %struct.obj_Int_struct* ()* @new_Int, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Obj_struct*)* @Int_method_EQUALS, %struct.obj_Obj_struct* (%struct.obj_Obj_struct*)* @Obj_method_PRINT, %struct.obj_String_struct* (%struct.obj_Int_struct*)* @Int_method_STR, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* @Int_method_ATLEAST, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* @Int_method_ATMOST, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* @Int_method_DIVIDE, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* @Int_method_LESS, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* @Int_method_MINUS, %struct.obj_Boolean_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* @Int_method_MORE, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* @Int_method_PLUS, %struct.obj_Int_struct* (%struct.obj_Int_struct*, %struct.obj_Int_struct*)* @Int_method_TIMES }, align 8

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Obj_struct* @new_Obj() #0 {
  %1 = alloca %struct.obj_Obj_struct*, align 8
  %2 = call i8* @malloc(i64 8) #4
  %3 = bitcast i8* %2 to %struct.obj_Obj_struct*
  store %struct.obj_Obj_struct* %3, %struct.obj_Obj_struct** %1, align 8
  %4 = load %struct.class_Obj_struct*, %struct.class_Obj_struct** @the_class_Obj, align 8
  %5 = load %struct.obj_Obj_struct*, %struct.obj_Obj_struct** %1, align 8
  %6 = getelementptr inbounds %struct.obj_Obj_struct, %struct.obj_Obj_struct* %5, i32 0, i32 0
  store %struct.class_Obj_struct* %4, %struct.class_Obj_struct** %6, align 8
  %7 = load %struct.obj_Obj_struct*, %struct.obj_Obj_struct** %1, align 8
  ret %struct.obj_Obj_struct* %7
}

; Function Attrs: allocsize(0)
declare i8* @malloc(i64) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_String_struct* @Obj_method_STR(%struct.obj_Obj_struct* %0) #0 {
  %2 = alloca %struct.obj_Obj_struct*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca %struct.obj_String_struct*, align 8
  store %struct.obj_Obj_struct* %0, %struct.obj_Obj_struct** %2, align 8
  %5 = load %struct.obj_Obj_struct*, %struct.obj_Obj_struct** %2, align 8
  %6 = ptrtoint %struct.obj_Obj_struct* %5 to i32
  %7 = call i32 (i8**, i8*, ...) @asprintf(i8** %3, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str, i64 0, i64 0), i32 %6)
  %8 = load i8*, i8** %3, align 8
  %9 = call %struct.obj_String_struct* @str_literal(i8* %8)
  store %struct.obj_String_struct* %9, %struct.obj_String_struct** %4, align 8
  %10 = load %struct.obj_String_struct*, %struct.obj_String_struct** %4, align 8
  ret %struct.obj_String_struct* %10
}

declare i32 @asprintf(i8**, i8*, ...) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_String_struct* @str_literal(i8* %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca %struct.obj_String_struct*, align 8
  store i8* %0, i8** %2, align 8
  %5 = load %struct.class_String_struct*, %struct.class_String_struct** @the_class_String, align 8
  %6 = getelementptr inbounds %struct.class_String_struct, %struct.class_String_struct* %5, i32 0, i32 1
  %7 = load %struct.obj_String_struct* ()*, %struct.obj_String_struct* ()** %6, align 8
  %8 = call %struct.obj_String_struct* %7()
  store %struct.obj_String_struct* %8, %struct.obj_String_struct** %4, align 8
  %9 = load i8*, i8** %2, align 8
  %10 = load %struct.obj_String_struct*, %struct.obj_String_struct** %4, align 8
  %11 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %10, i32 0, i32 1
  store i8* %9, i8** %11, align 8
  %12 = load %struct.obj_String_struct*, %struct.obj_String_struct** %4, align 8
  ret %struct.obj_String_struct* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Obj_struct* @Obj_method_PRINT(%struct.obj_Obj_struct* %0) #0 {
  %2 = alloca %struct.obj_Obj_struct*, align 8
  %3 = alloca %struct.obj_String_struct*, align 8
  store %struct.obj_Obj_struct* %0, %struct.obj_Obj_struct** %2, align 8
  %4 = load %struct.obj_Obj_struct*, %struct.obj_Obj_struct** %2, align 8
  %5 = getelementptr inbounds %struct.obj_Obj_struct, %struct.obj_Obj_struct* %4, i32 0, i32 0
  %6 = load %struct.class_Obj_struct*, %struct.class_Obj_struct** %5, align 8
  %7 = getelementptr inbounds %struct.class_Obj_struct, %struct.class_Obj_struct* %6, i32 0, i32 4
  %8 = load %struct.obj_String_struct* (%struct.obj_Obj_struct*)*, %struct.obj_String_struct* (%struct.obj_Obj_struct*)** %7, align 8
  %9 = load %struct.obj_Obj_struct*, %struct.obj_Obj_struct** %2, align 8
  %10 = call %struct.obj_String_struct* %8(%struct.obj_Obj_struct* %9)
  store %struct.obj_String_struct* %10, %struct.obj_String_struct** %3, align 8
  %11 = load %struct.__sFILE*, %struct.__sFILE** @__stdoutp, align 8
  %12 = load %struct.obj_String_struct*, %struct.obj_String_struct** %3, align 8
  %13 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %12, i32 0, i32 1
  %14 = load i8*, i8** %13, align 8
  %15 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %11, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i64 0, i64 0), i8* %14)
  %16 = load %struct.obj_Obj_struct*, %struct.obj_Obj_struct** %2, align 8
  ret %struct.obj_Obj_struct* %16
}

declare i32 @fprintf(%struct.__sFILE*, i8*, ...) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @Obj_method_EQUALS(%struct.obj_Obj_struct* %0, %struct.obj_Obj_struct* %1) #0 {
  %3 = alloca %struct.obj_Boolean_struct*, align 8
  %4 = alloca %struct.obj_Obj_struct*, align 8
  %5 = alloca %struct.obj_Obj_struct*, align 8
  store %struct.obj_Obj_struct* %0, %struct.obj_Obj_struct** %4, align 8
  store %struct.obj_Obj_struct* %1, %struct.obj_Obj_struct** %5, align 8
  %6 = load %struct.obj_Obj_struct*, %struct.obj_Obj_struct** %4, align 8
  %7 = load %struct.obj_Obj_struct*, %struct.obj_Obj_struct** %5, align 8
  %8 = icmp eq %struct.obj_Obj_struct* %6, %7
  br i1 %8, label %9, label %11

9:                                                ; preds = %2
  %10 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  store %struct.obj_Boolean_struct* %10, %struct.obj_Boolean_struct** %3, align 8
  br label %13

11:                                               ; preds = %2
  %12 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  store %struct.obj_Boolean_struct* %12, %struct.obj_Boolean_struct** %3, align 8
  br label %13

13:                                               ; preds = %11, %9
  %14 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** %3, align 8
  ret %struct.obj_Boolean_struct* %14
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_String_struct* @new_String() #0 {
  %1 = alloca %struct.obj_String_struct*, align 8
  %2 = call i8* @malloc(i64 16) #4
  %3 = bitcast i8* %2 to %struct.obj_String_struct*
  store %struct.obj_String_struct* %3, %struct.obj_String_struct** %1, align 8
  %4 = load %struct.class_String_struct*, %struct.class_String_struct** @the_class_String, align 8
  %5 = load %struct.obj_String_struct*, %struct.obj_String_struct** %1, align 8
  %6 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %5, i32 0, i32 0
  store %struct.class_String_struct* %4, %struct.class_String_struct** %6, align 8
  %7 = load %struct.obj_String_struct*, %struct.obj_String_struct** %1, align 8
  ret %struct.obj_String_struct* %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_String_struct* @String_method_STR(%struct.obj_String_struct* %0) #0 {
  %2 = alloca %struct.obj_String_struct*, align 8
  store %struct.obj_String_struct* %0, %struct.obj_String_struct** %2, align 8
  %3 = load %struct.obj_String_struct*, %struct.obj_String_struct** %2, align 8
  ret %struct.obj_String_struct* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @String_method_EQUALS(%struct.obj_String_struct* %0, %struct.obj_Obj_struct* %1) #0 {
  %3 = alloca %struct.obj_Boolean_struct*, align 8
  %4 = alloca %struct.obj_String_struct*, align 8
  %5 = alloca %struct.obj_Obj_struct*, align 8
  %6 = alloca %struct.obj_String_struct*, align 8
  store %struct.obj_String_struct* %0, %struct.obj_String_struct** %4, align 8
  store %struct.obj_Obj_struct* %1, %struct.obj_Obj_struct** %5, align 8
  %7 = load %struct.obj_Obj_struct*, %struct.obj_Obj_struct** %5, align 8
  %8 = bitcast %struct.obj_Obj_struct* %7 to %struct.obj_String_struct*
  store %struct.obj_String_struct* %8, %struct.obj_String_struct** %6, align 8
  %9 = load %struct.obj_String_struct*, %struct.obj_String_struct** %6, align 8
  %10 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %9, i32 0, i32 0
  %11 = load %struct.class_String_struct*, %struct.class_String_struct** %10, align 8
  %12 = load %struct.class_String_struct*, %struct.class_String_struct** @the_class_String, align 8
  %13 = icmp eq %struct.class_String_struct* %11, %12
  br i1 %13, label %14, label %25

14:                                               ; preds = %2
  %15 = load %struct.obj_String_struct*, %struct.obj_String_struct** %4, align 8
  %16 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %15, i32 0, i32 1
  %17 = load i8*, i8** %16, align 8
  %18 = load %struct.obj_String_struct*, %struct.obj_String_struct** %6, align 8
  %19 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %18, i32 0, i32 1
  %20 = load i8*, i8** %19, align 8
  %21 = call i32 @strcmp(i8* %17, i8* %20)
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %23, label %25

23:                                               ; preds = %14
  %24 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  store %struct.obj_Boolean_struct* %24, %struct.obj_Boolean_struct** %3, align 8
  br label %27

25:                                               ; preds = %14, %2
  %26 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  store %struct.obj_Boolean_struct* %26, %struct.obj_Boolean_struct** %3, align 8
  br label %27

27:                                               ; preds = %25, %23
  %28 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** %3, align 8
  ret %struct.obj_Boolean_struct* %28
}

declare i32 @strcmp(i8*, i8*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_String_struct* @String_method_PLUS(%struct.obj_String_struct* %0, %struct.obj_String_struct* %1) #0 {
  %3 = alloca %struct.obj_String_struct*, align 8
  %4 = alloca %struct.obj_String_struct*, align 8
  %5 = alloca i8*, align 8
  store %struct.obj_String_struct* %0, %struct.obj_String_struct** %3, align 8
  store %struct.obj_String_struct* %1, %struct.obj_String_struct** %4, align 8
  %6 = load %struct.obj_String_struct*, %struct.obj_String_struct** %3, align 8
  %7 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %6, i32 0, i32 1
  %8 = load i8*, i8** %7, align 8
  %9 = load %struct.obj_String_struct*, %struct.obj_String_struct** %4, align 8
  %10 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %9, i32 0, i32 1
  %11 = load i8*, i8** %10, align 8
  %12 = call i32 (i8**, i8*, ...) @asprintf(i8** %5, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0), i8* %8, i8* %11)
  %13 = load i8*, i8** %5, align 8
  %14 = call %struct.obj_String_struct* @str_literal(i8* %13)
  ret %struct.obj_String_struct* %14
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @String_method_LESS(%struct.obj_String_struct* %0, %struct.obj_String_struct* %1) #0 {
  %3 = alloca %struct.obj_String_struct*, align 8
  %4 = alloca %struct.obj_String_struct*, align 8
  store %struct.obj_String_struct* %0, %struct.obj_String_struct** %3, align 8
  store %struct.obj_String_struct* %1, %struct.obj_String_struct** %4, align 8
  %5 = load %struct.obj_String_struct*, %struct.obj_String_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %5, i32 0, i32 1
  %7 = load i8*, i8** %6, align 8
  %8 = load %struct.obj_String_struct*, %struct.obj_String_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %8, i32 0, i32 1
  %10 = load i8*, i8** %9, align 8
  %11 = call i32 @strcmp(i8* %7, i8* %10)
  %12 = icmp slt i32 %11, 0
  br i1 %12, label %13, label %15

13:                                               ; preds = %2
  %14 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  br label %17

15:                                               ; preds = %2
  %16 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  br label %17

17:                                               ; preds = %15, %13
  %18 = phi %struct.obj_Boolean_struct* [ %14, %13 ], [ %16, %15 ]
  ret %struct.obj_Boolean_struct* %18
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @String_method_MORE(%struct.obj_String_struct* %0, %struct.obj_String_struct* %1) #0 {
  %3 = alloca %struct.obj_String_struct*, align 8
  %4 = alloca %struct.obj_String_struct*, align 8
  store %struct.obj_String_struct* %0, %struct.obj_String_struct** %3, align 8
  store %struct.obj_String_struct* %1, %struct.obj_String_struct** %4, align 8
  %5 = load %struct.obj_String_struct*, %struct.obj_String_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %5, i32 0, i32 1
  %7 = load i8*, i8** %6, align 8
  %8 = load %struct.obj_String_struct*, %struct.obj_String_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %8, i32 0, i32 1
  %10 = load i8*, i8** %9, align 8
  %11 = call i32 @strcmp(i8* %7, i8* %10)
  %12 = icmp sgt i32 %11, 0
  br i1 %12, label %13, label %15

13:                                               ; preds = %2
  %14 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  br label %17

15:                                               ; preds = %2
  %16 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  br label %17

17:                                               ; preds = %15, %13
  %18 = phi %struct.obj_Boolean_struct* [ %14, %13 ], [ %16, %15 ]
  ret %struct.obj_Boolean_struct* %18
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @String_method_ATLEAST(%struct.obj_String_struct* %0, %struct.obj_String_struct* %1) #0 {
  %3 = alloca %struct.obj_String_struct*, align 8
  %4 = alloca %struct.obj_String_struct*, align 8
  store %struct.obj_String_struct* %0, %struct.obj_String_struct** %3, align 8
  store %struct.obj_String_struct* %1, %struct.obj_String_struct** %4, align 8
  %5 = load %struct.obj_String_struct*, %struct.obj_String_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %5, i32 0, i32 1
  %7 = load i8*, i8** %6, align 8
  %8 = load %struct.obj_String_struct*, %struct.obj_String_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %8, i32 0, i32 1
  %10 = load i8*, i8** %9, align 8
  %11 = call i32 @strcmp(i8* %7, i8* %10)
  %12 = icmp sle i32 %11, 0
  br i1 %12, label %13, label %15

13:                                               ; preds = %2
  %14 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  br label %17

15:                                               ; preds = %2
  %16 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  br label %17

17:                                               ; preds = %15, %13
  %18 = phi %struct.obj_Boolean_struct* [ %14, %13 ], [ %16, %15 ]
  ret %struct.obj_Boolean_struct* %18
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @String_method_ATMOST(%struct.obj_String_struct* %0, %struct.obj_String_struct* %1) #0 {
  %3 = alloca %struct.obj_String_struct*, align 8
  %4 = alloca %struct.obj_String_struct*, align 8
  store %struct.obj_String_struct* %0, %struct.obj_String_struct** %3, align 8
  store %struct.obj_String_struct* %1, %struct.obj_String_struct** %4, align 8
  %5 = load %struct.obj_String_struct*, %struct.obj_String_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %5, i32 0, i32 1
  %7 = load i8*, i8** %6, align 8
  %8 = load %struct.obj_String_struct*, %struct.obj_String_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_String_struct, %struct.obj_String_struct* %8, i32 0, i32 1
  %10 = load i8*, i8** %9, align 8
  %11 = call i32 @strcmp(i8* %7, i8* %10)
  %12 = icmp sge i32 %11, 0
  br i1 %12, label %13, label %15

13:                                               ; preds = %2
  %14 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  br label %17

15:                                               ; preds = %2
  %16 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  br label %17

17:                                               ; preds = %15, %13
  %18 = phi %struct.obj_Boolean_struct* [ %14, %13 ], [ %16, %15 ]
  ret %struct.obj_Boolean_struct* %18
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @new_Boolean() #0 {
  %1 = alloca %struct.obj_Boolean_struct*, align 8
  %2 = call i8* @malloc(i64 16) #4
  %3 = bitcast i8* %2 to %struct.obj_Boolean_struct*
  store %struct.obj_Boolean_struct* %3, %struct.obj_Boolean_struct** %1, align 8
  %4 = load %struct.class_Boolean_struct*, %struct.class_Boolean_struct** @the_class_Boolean, align 8
  %5 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** %1, align 8
  %6 = getelementptr inbounds %struct.obj_Boolean_struct, %struct.obj_Boolean_struct* %5, i32 0, i32 0
  store %struct.class_Boolean_struct* %4, %struct.class_Boolean_struct** %6, align 8
  %7 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** %1, align 8
  ret %struct.obj_Boolean_struct* %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_String_struct* @Boolean_method_STR(%struct.obj_Boolean_struct* %0) #0 {
  %2 = alloca %struct.obj_String_struct*, align 8
  %3 = alloca %struct.obj_Boolean_struct*, align 8
  store %struct.obj_Boolean_struct* %0, %struct.obj_Boolean_struct** %3, align 8
  %4 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** %3, align 8
  %5 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  %6 = icmp eq %struct.obj_Boolean_struct* %4, %5
  br i1 %6, label %7, label %9

7:                                                ; preds = %1
  %8 = call %struct.obj_String_struct* @str_literal(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0))
  store %struct.obj_String_struct* %8, %struct.obj_String_struct** %2, align 8
  br label %18

9:                                                ; preds = %1
  %10 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** %3, align 8
  %11 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  %12 = icmp eq %struct.obj_Boolean_struct* %10, %11
  br i1 %12, label %13, label %15

13:                                               ; preds = %9
  %14 = call %struct.obj_String_struct* @str_literal(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.4, i64 0, i64 0))
  store %struct.obj_String_struct* %14, %struct.obj_String_struct** %2, align 8
  br label %18

15:                                               ; preds = %9
  %16 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %17 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %16, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.5, i64 0, i64 0))
  call void @exit(i32 1) #5
  unreachable

18:                                               ; preds = %13, %7
  %19 = load %struct.obj_String_struct*, %struct.obj_String_struct** %2, align 8
  ret %struct.obj_String_struct* %19
}

; Function Attrs: noreturn
declare void @exit(i32) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Nothing_struct* @new_Nothing() #0 {
  %1 = load %struct.obj_Nothing_struct*, %struct.obj_Nothing_struct** @none, align 8
  ret %struct.obj_Nothing_struct* %1
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_String_struct* @Nothing_method_STR(%struct.obj_Nothing_struct* %0) #0 {
  %2 = alloca %struct.obj_Nothing_struct*, align 8
  store %struct.obj_Nothing_struct* %0, %struct.obj_Nothing_struct** %2, align 8
  %3 = call %struct.obj_String_struct* @str_literal(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.6, i64 0, i64 0))
  ret %struct.obj_String_struct* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Int_struct* @new_Int() #0 {
  %1 = alloca %struct.obj_Int_struct*, align 8
  %2 = call i8* @malloc(i64 16) #4
  %3 = bitcast i8* %2 to %struct.obj_Int_struct*
  store %struct.obj_Int_struct* %3, %struct.obj_Int_struct** %1, align 8
  %4 = load %struct.class_Int_struct*, %struct.class_Int_struct** @the_class_Int, align 8
  %5 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %1, align 8
  %6 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %5, i32 0, i32 0
  store %struct.class_Int_struct* %4, %struct.class_Int_struct** %6, align 8
  %7 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %1, align 8
  %8 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %7, i32 0, i32 1
  store i32 0, i32* %8, align 8
  %9 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %1, align 8
  ret %struct.obj_Int_struct* %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_String_struct* @Int_method_STR(%struct.obj_Int_struct* %0) #0 {
  %2 = alloca %struct.obj_Int_struct*, align 8
  %3 = alloca i8*, align 8
  store %struct.obj_Int_struct* %0, %struct.obj_Int_struct** %2, align 8
  %4 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %2, align 8
  %5 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %4, i32 0, i32 1
  %6 = load i32, i32* %5, align 8
  %7 = call i32 (i8**, i8*, ...) @asprintf(i8** %3, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.7, i64 0, i64 0), i32 %6)
  %8 = load i8*, i8** %3, align 8
  %9 = call %struct.obj_String_struct* @str_literal(i8* %8)
  ret %struct.obj_String_struct* %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @Int_method_EQUALS(%struct.obj_Int_struct* %0, %struct.obj_Obj_struct* %1) #0 {
  %3 = alloca %struct.obj_Boolean_struct*, align 8
  %4 = alloca %struct.obj_Int_struct*, align 8
  %5 = alloca %struct.obj_Obj_struct*, align 8
  %6 = alloca %struct.obj_Int_struct*, align 8
  store %struct.obj_Int_struct* %0, %struct.obj_Int_struct** %4, align 8
  store %struct.obj_Obj_struct* %1, %struct.obj_Obj_struct** %5, align 8
  %7 = load %struct.obj_Obj_struct*, %struct.obj_Obj_struct** %5, align 8
  %8 = bitcast %struct.obj_Obj_struct* %7 to %struct.obj_Int_struct*
  store %struct.obj_Int_struct* %8, %struct.obj_Int_struct** %6, align 8
  %9 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %6, align 8
  %10 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %9, i32 0, i32 0
  %11 = load %struct.class_Int_struct*, %struct.class_Int_struct** %10, align 8
  %12 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %4, align 8
  %13 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %12, i32 0, i32 0
  %14 = load %struct.class_Int_struct*, %struct.class_Int_struct** %13, align 8
  %15 = icmp ne %struct.class_Int_struct* %11, %14
  br i1 %15, label %24, label %16

16:                                               ; preds = %2
  %17 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %4, align 8
  %18 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %17, i32 0, i32 1
  %19 = load i32, i32* %18, align 8
  %20 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %6, align 8
  %21 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %20, i32 0, i32 1
  %22 = load i32, i32* %21, align 8
  %23 = icmp ne i32 %19, %22
  br i1 %23, label %24, label %26

24:                                               ; preds = %16, %2
  %25 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  store %struct.obj_Boolean_struct* %25, %struct.obj_Boolean_struct** %3, align 8
  br label %28

26:                                               ; preds = %16
  %27 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  store %struct.obj_Boolean_struct* %27, %struct.obj_Boolean_struct** %3, align 8
  br label %28

28:                                               ; preds = %26, %24
  %29 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** %3, align 8
  ret %struct.obj_Boolean_struct* %29
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @Int_method_LESS(%struct.obj_Int_struct* %0, %struct.obj_Int_struct* %1) #0 {
  %3 = alloca %struct.obj_Int_struct*, align 8
  %4 = alloca %struct.obj_Int_struct*, align 8
  store %struct.obj_Int_struct* %0, %struct.obj_Int_struct** %3, align 8
  store %struct.obj_Int_struct* %1, %struct.obj_Int_struct** %4, align 8
  %5 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 8
  %8 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %8, i32 0, i32 1
  %10 = load i32, i32* %9, align 8
  %11 = icmp slt i32 %7, %10
  br i1 %11, label %12, label %14

12:                                               ; preds = %2
  %13 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  br label %16

14:                                               ; preds = %2
  %15 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  br label %16

16:                                               ; preds = %14, %12
  %17 = phi %struct.obj_Boolean_struct* [ %13, %12 ], [ %15, %14 ]
  ret %struct.obj_Boolean_struct* %17
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @Int_method_MORE(%struct.obj_Int_struct* %0, %struct.obj_Int_struct* %1) #0 {
  %3 = alloca %struct.obj_Int_struct*, align 8
  %4 = alloca %struct.obj_Int_struct*, align 8
  store %struct.obj_Int_struct* %0, %struct.obj_Int_struct** %3, align 8
  store %struct.obj_Int_struct* %1, %struct.obj_Int_struct** %4, align 8
  %5 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 8
  %8 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %8, i32 0, i32 1
  %10 = load i32, i32* %9, align 8
  %11 = icmp sgt i32 %7, %10
  br i1 %11, label %12, label %14

12:                                               ; preds = %2
  %13 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  br label %16

14:                                               ; preds = %2
  %15 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  br label %16

16:                                               ; preds = %14, %12
  %17 = phi %struct.obj_Boolean_struct* [ %13, %12 ], [ %15, %14 ]
  ret %struct.obj_Boolean_struct* %17
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @Int_method_ATMOST(%struct.obj_Int_struct* %0, %struct.obj_Int_struct* %1) #0 {
  %3 = alloca %struct.obj_Int_struct*, align 8
  %4 = alloca %struct.obj_Int_struct*, align 8
  store %struct.obj_Int_struct* %0, %struct.obj_Int_struct** %3, align 8
  store %struct.obj_Int_struct* %1, %struct.obj_Int_struct** %4, align 8
  %5 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 8
  %8 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %8, i32 0, i32 1
  %10 = load i32, i32* %9, align 8
  %11 = icmp sle i32 %7, %10
  br i1 %11, label %12, label %14

12:                                               ; preds = %2
  %13 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  br label %16

14:                                               ; preds = %2
  %15 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  br label %16

16:                                               ; preds = %14, %12
  %17 = phi %struct.obj_Boolean_struct* [ %13, %12 ], [ %15, %14 ]
  ret %struct.obj_Boolean_struct* %17
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Boolean_struct* @Int_method_ATLEAST(%struct.obj_Int_struct* %0, %struct.obj_Int_struct* %1) #0 {
  %3 = alloca %struct.obj_Int_struct*, align 8
  %4 = alloca %struct.obj_Int_struct*, align 8
  store %struct.obj_Int_struct* %0, %struct.obj_Int_struct** %3, align 8
  store %struct.obj_Int_struct* %1, %struct.obj_Int_struct** %4, align 8
  %5 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 8
  %8 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %8, i32 0, i32 1
  %10 = load i32, i32* %9, align 8
  %11 = icmp sge i32 %7, %10
  br i1 %11, label %12, label %14

12:                                               ; preds = %2
  %13 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  br label %16

14:                                               ; preds = %2
  %15 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_false, align 8
  br label %16

16:                                               ; preds = %14, %12
  %17 = phi %struct.obj_Boolean_struct* [ %13, %12 ], [ %15, %14 ]
  ret %struct.obj_Boolean_struct* %17
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Int_struct* @Int_method_PLUS(%struct.obj_Int_struct* %0, %struct.obj_Int_struct* %1) #0 {
  %3 = alloca %struct.obj_Int_struct*, align 8
  %4 = alloca %struct.obj_Int_struct*, align 8
  store %struct.obj_Int_struct* %0, %struct.obj_Int_struct** %3, align 8
  store %struct.obj_Int_struct* %1, %struct.obj_Int_struct** %4, align 8
  %5 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 8
  %8 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %8, i32 0, i32 1
  %10 = load i32, i32* %9, align 8
  %11 = add nsw i32 %7, %10
  %12 = call %struct.obj_Int_struct* @int_literal(i32 %11)
  ret %struct.obj_Int_struct* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Int_struct* @int_literal(i32 %0) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.obj_Int_struct*, align 8
  store i32 %0, i32* %2, align 4
  %4 = call %struct.obj_Int_struct* @new_Int()
  store %struct.obj_Int_struct* %4, %struct.obj_Int_struct** %3, align 8
  %5 = load i32, i32* %2, align 4
  %6 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %3, align 8
  %7 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %6, i32 0, i32 1
  store i32 %5, i32* %7, align 8
  %8 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %3, align 8
  ret %struct.obj_Int_struct* %8
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Int_struct* @Int_method_MINUS(%struct.obj_Int_struct* %0, %struct.obj_Int_struct* %1) #0 {
  %3 = alloca %struct.obj_Int_struct*, align 8
  %4 = alloca %struct.obj_Int_struct*, align 8
  store %struct.obj_Int_struct* %0, %struct.obj_Int_struct** %3, align 8
  store %struct.obj_Int_struct* %1, %struct.obj_Int_struct** %4, align 8
  %5 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 8
  %8 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %8, i32 0, i32 1
  %10 = load i32, i32* %9, align 8
  %11 = sub nsw i32 %7, %10
  %12 = call %struct.obj_Int_struct* @int_literal(i32 %11)
  ret %struct.obj_Int_struct* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Int_struct* @Int_method_TIMES(%struct.obj_Int_struct* %0, %struct.obj_Int_struct* %1) #0 {
  %3 = alloca %struct.obj_Int_struct*, align 8
  %4 = alloca %struct.obj_Int_struct*, align 8
  store %struct.obj_Int_struct* %0, %struct.obj_Int_struct** %3, align 8
  store %struct.obj_Int_struct* %1, %struct.obj_Int_struct** %4, align 8
  %5 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 8
  %8 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %8, i32 0, i32 1
  %10 = load i32, i32* %9, align 8
  %11 = mul nsw i32 %7, %10
  %12 = call %struct.obj_Int_struct* @int_literal(i32 %11)
  ret %struct.obj_Int_struct* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.obj_Int_struct* @Int_method_DIVIDE(%struct.obj_Int_struct* %0, %struct.obj_Int_struct* %1) #0 {
  %3 = alloca %struct.obj_Int_struct*, align 8
  %4 = alloca %struct.obj_Int_struct*, align 8
  store %struct.obj_Int_struct* %0, %struct.obj_Int_struct** %3, align 8
  store %struct.obj_Int_struct* %1, %struct.obj_Int_struct** %4, align 8
  %5 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %3, align 8
  %6 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %5, i32 0, i32 1
  %7 = load i32, i32* %6, align 8
  %8 = load %struct.obj_Int_struct*, %struct.obj_Int_struct** %4, align 8
  %9 = getelementptr inbounds %struct.obj_Int_struct, %struct.obj_Int_struct* %8, i32 0, i32 1
  %10 = load i32, i32* %9, align 8
  %11 = sdiv i32 %7, %10
  %12 = call %struct.obj_Int_struct* @int_literal(i32 %11)
  ret %struct.obj_Int_struct* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local zeroext i1 @is_subtype(%struct.class_Obj_struct* %0, %struct.class_Obj_struct* %1) #0 {
  %3 = alloca i1, align 1
  %4 = alloca %struct.class_Obj_struct*, align 8
  %5 = alloca %struct.class_Obj_struct*, align 8
  store %struct.class_Obj_struct* %0, %struct.class_Obj_struct** %4, align 8
  store %struct.class_Obj_struct* %1, %struct.class_Obj_struct** %5, align 8
  %6 = load %struct.class_Obj_struct*, %struct.class_Obj_struct** %4, align 8
  %7 = load %struct.class_Obj_struct*, %struct.class_Obj_struct** %5, align 8
  %8 = icmp eq %struct.class_Obj_struct* %6, %7
  br i1 %8, label %9, label %10

9:                                                ; preds = %2
  store i1 true, i1* %3, align 1
  br label %22

10:                                               ; preds = %2
  %11 = load %struct.class_Obj_struct*, %struct.class_Obj_struct** %4, align 8
  %12 = getelementptr inbounds %struct.class_Obj_struct, %struct.class_Obj_struct* %11, i32 0, i32 0
  %13 = load %struct.class_Obj_struct*, %struct.class_Obj_struct** %12, align 8
  %14 = icmp eq %struct.class_Obj_struct* %13, null
  br i1 %14, label %15, label %16

15:                                               ; preds = %10
  store i1 false, i1* %3, align 1
  br label %22

16:                                               ; preds = %10
  %17 = load %struct.class_Obj_struct*, %struct.class_Obj_struct** %4, align 8
  %18 = getelementptr inbounds %struct.class_Obj_struct, %struct.class_Obj_struct* %17, i32 0, i32 0
  %19 = load %struct.class_Obj_struct*, %struct.class_Obj_struct** %18, align 8
  %20 = load %struct.class_Obj_struct*, %struct.class_Obj_struct** %5, align 8
  %21 = call zeroext i1 @is_subtype(%struct.class_Obj_struct* %19, %struct.class_Obj_struct* %20)
  store i1 %21, i1* %3, align 1
  br label %22

22:                                               ; preds = %16, %15, %9
  %23 = load i1, i1* %3, align 1
  ret i1 %23
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local zeroext i1 @is_bool_true(%struct.obj_Boolean_struct* %0) #0 {
  %2 = alloca %struct.obj_Boolean_struct*, align 8
  store %struct.obj_Boolean_struct* %0, %struct.obj_Boolean_struct** %2, align 8
  %3 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** %2, align 8
  %4 = load %struct.obj_Boolean_struct*, %struct.obj_Boolean_struct** @lit_true, align 8
  %5 = icmp eq %struct.obj_Boolean_struct* %3, %4
  ret i1 %5
}

attributes #0 = { noinline nounwind optnone ssp uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { allocsize(0) "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { allocsize(0) }
attributes #5 = { noreturn }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 12.0.0"}
