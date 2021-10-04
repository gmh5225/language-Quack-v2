; ModuleID = 'quack_runtime.c'
source_filename = "quack_runtime.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.ObjectVTable = type { %struct.Boolean* (%struct.Object*, %struct.Object*)*, %struct.Nothing* (%struct.Object*)*, %struct.Nothing* (%struct.Object*)* }
%struct.Boolean = type { %struct.header, %struct.BooleanVTable*, i64 }
%struct.header = type { i64, i32 }
%struct.BooleanVTable = type { %struct.Boolean* (%struct.Boolean*, %struct.Boolean*)*, %struct.Nothing* (%struct.Boolean*)*, %struct.Nothing* (%struct.Boolean*)* }
%struct.Nothing = type { %struct.header, %struct.NothingVTable* }
%struct.NothingVTable = type { %struct.Boolean* (%struct.Nothing*, %struct.Nothing*)*, %struct.Nothing* (%struct.Nothing*)*, %struct.Nothing* (%struct.Nothing*)* }
%struct.Object = type { %struct.header, %struct.ObjectVTable* }
%struct.IntegerVTable = type { %struct.Boolean* (%struct.Integer*, %struct.Integer*)*, %struct.Nothing* (%struct.Integer*)*, %struct.Nothing* (%struct.Object*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)*, %struct.Integer* (%struct.Integer*, %struct.Integer*)* }
%struct.Integer = type { %struct.header, %struct.IntegerVTable*, i64 }
%struct.FloatVTable = type { %struct.Boolean* (%struct.Float*, %struct.Float*)*, %struct.Nothing* (%struct.Float*)*, %struct.Nothing* (%struct.Object*)*, %struct.Float* (%struct.Float*, %struct.Float*)*, %struct.Float* (%struct.Float*, %struct.Float*)*, %struct.Float* (%struct.Float*, %struct.Float*)*, %struct.Float* (%struct.Float*, %struct.Float*)*, %struct.Float* (%struct.Float*, %struct.Float*)*, %struct.Float* (%struct.Float*, %struct.Float*)*, %struct.Float* (%struct.Float*, %struct.Float*)*, %struct.Float* (%struct.Float*, %struct.Float*)* }
%struct.Float = type { %struct.header, %struct.FloatVTable*, double }
%struct.StringVTable = type { %struct.Boolean* (%struct.String*, %struct.String*)*, %struct.Nothing* (%struct.String*)*, %struct.Nothing* (%struct.String*)*, %struct.String* (%struct.String*, %struct.String*)* }
%struct.String = type { %struct.header, %struct.StringVTable*, i8* }
%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.__sFILEX = type opaque
%struct.__sbuf = type { i8*, i32 }

@__func__.newObject = private unnamed_addr constant [10 x i8] c"newObject\00", align 1
@.str = private unnamed_addr constant [16 x i8] c"quack_runtime.c\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"newObj\00", align 1
@ObjectVTTemplate = internal global %struct.ObjectVTable { %struct.Boolean* (%struct.Object*, %struct.Object*)* @equalsObject, %struct.Nothing* (%struct.Object*)* @printObject, %struct.Nothing* (%struct.Object*)* @destroyObject }, align 8
@Nothing = internal global %struct.Nothing { %struct.header { i64 0, i32 -1 }, %struct.NothingVTable* @NothingVTTemplate }, align 8
@True = internal global %struct.Boolean { %struct.header { i64 0, i32 -3 }, %struct.BooleanVTable* @BooleanVTTemplate, i64 1 }, align 8
@False = internal global %struct.Boolean { %struct.header { i64 0, i32 -3 }, %struct.BooleanVTable* @BooleanVTTemplate, i64 0 }, align 8
@__func__.newInteger = private unnamed_addr constant [11 x i8] c"newInteger\00", align 1
@IntegerVTTemplate = internal global %struct.IntegerVTable { %struct.Boolean* (%struct.Integer*, %struct.Integer*)* @equalsInteger, %struct.Nothing* (%struct.Integer*)* @printInteger, %struct.Nothing* (%struct.Object*)* @destroyObject, %struct.Integer* (%struct.Integer*, %struct.Integer*)* @addInteger, %struct.Integer* (%struct.Integer*, %struct.Integer*)* @mulInteger, %struct.Integer* (%struct.Integer*, %struct.Integer*)* @subInteger, %struct.Integer* (%struct.Integer*, %struct.Integer*)* @divInteger, %struct.Integer* (%struct.Integer*, %struct.Integer*)* @modInteger, %struct.Integer* (%struct.Integer*, %struct.Integer*)* null, %struct.Integer* (%struct.Integer*, %struct.Integer*)* null, %struct.Integer* (%struct.Integer*, %struct.Integer*)* null, %struct.Integer* (%struct.Integer*, %struct.Integer*)* null }, align 8
@__func__.newFloat = private unnamed_addr constant [9 x i8] c"newFloat\00", align 1
@FloatVTTemplate = internal global %struct.FloatVTable { %struct.Boolean* (%struct.Float*, %struct.Float*)* @equalsFloat, %struct.Nothing* (%struct.Float*)* @printFloat, %struct.Nothing* (%struct.Object*)* @destroyObject, %struct.Float* (%struct.Float*, %struct.Float*)* @addFloat, %struct.Float* (%struct.Float*, %struct.Float*)* @mulFloat, %struct.Float* (%struct.Float*, %struct.Float*)* @subFloat, %struct.Float* (%struct.Float*, %struct.Float*)* @divFloat, %struct.Float* (%struct.Float*, %struct.Float*)* null, %struct.Float* (%struct.Float*, %struct.Float*)* null, %struct.Float* (%struct.Float*, %struct.Float*)* null, %struct.Float* (%struct.Float*, %struct.Float*)* null }, align 8
@__func__.newString = private unnamed_addr constant [10 x i8] c"newString\00", align 1
@.str.2 = private unnamed_addr constant [7 x i8] c"newStr\00", align 1
@StringVTTemplate = internal global %struct.StringVTable { %struct.Boolean* (%struct.String*, %struct.String*)* @equalsString, %struct.Nothing* (%struct.String*)* @printString, %struct.Nothing* (%struct.String*)* @destroyString, %struct.String* (%struct.String*, %struct.String*)* @addString }, align 8
@.str.3 = private unnamed_addr constant [19 x i8] c"<Object at %08lx>\0A\00", align 1
@NothingVTTemplate = internal global %struct.NothingVTable { %struct.Boolean* (%struct.Nothing*, %struct.Nothing*)* @equalsNothing, %struct.Nothing* (%struct.Nothing*)* @printNothing, %struct.Nothing* (%struct.Nothing*)* @destroyNothing }, align 8
@.str.4 = private unnamed_addr constant [9 x i8] c"Nothing\0A\00", align 1
@BooleanVTTemplate = internal global %struct.BooleanVTable { %struct.Boolean* (%struct.Boolean*, %struct.Boolean*)* @equalsBoolean, %struct.Nothing* (%struct.Boolean*)* @printBoolean, %struct.Nothing* (%struct.Boolean*)* @destroyBoolean }, align 8
@.str.5 = private unnamed_addr constant [6 x i8] c"True\0A\00", align 1
@.str.6 = private unnamed_addr constant [7 x i8] c"False\0A\00", align 1
@.str.7 = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"%lf\0A\00", align 1
@__stdoutp = external global %struct.__sFILE*, align 8
@.str.9 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@__func__.addString = private unnamed_addr constant [10 x i8] c"addString\00", align 1
@.str.10 = private unnamed_addr constant [4 x i8] c"ptr\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local void @incrementRefCounter(%struct.Object* %0) #0 {
  %2 = alloca %struct.Object*, align 8
  store %struct.Object* %0, %struct.Object** %2, align 8
  %3 = load %struct.Object*, %struct.Object** %2, align 8
  %4 = getelementptr inbounds %struct.Object, %struct.Object* %3, i32 0, i32 0
  %5 = getelementptr inbounds %struct.header, %struct.header* %4, i32 0, i32 0
  %6 = load i64, i64* %5, align 8
  %7 = add i64 %6, 1
  store i64 %7, i64* %5, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local i32 @decrementRefCounter(%struct.Object* %0) #0 {
  %2 = alloca %struct.Object*, align 8
  store %struct.Object* %0, %struct.Object** %2, align 8
  %3 = load %struct.Object*, %struct.Object** %2, align 8
  %4 = getelementptr inbounds %struct.Object, %struct.Object* %3, i32 0, i32 0
  %5 = getelementptr inbounds %struct.header, %struct.header* %4, i32 0, i32 0
  %6 = load i64, i64* %5, align 8
  %7 = add i64 %6, -1
  store i64 %7, i64* %5, align 8
  %8 = trunc i64 %7 to i32
  ret i32 %8
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local i32 @isFalse(%struct.Boolean* %0) #0 {
  %2 = alloca %struct.Boolean*, align 8
  store %struct.Boolean* %0, %struct.Boolean** %2, align 8
  %3 = load %struct.Boolean*, %struct.Boolean** %2, align 8
  %4 = getelementptr inbounds %struct.Boolean, %struct.Boolean* %3, i32 0, i32 2
  %5 = load i64, i64* %4, align 8
  %6 = icmp eq i64 %5, 0
  %7 = zext i1 %6 to i32
  ret i32 %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local i32 @isTrue(%struct.Boolean* %0) #0 {
  %2 = alloca %struct.Boolean*, align 8
  store %struct.Boolean* %0, %struct.Boolean** %2, align 8
  %3 = load %struct.Boolean*, %struct.Boolean** %2, align 8
  %4 = getelementptr inbounds %struct.Boolean, %struct.Boolean* %3, i32 0, i32 2
  %5 = load i64, i64* %4, align 8
  %6 = icmp eq i64 %5, 1
  %7 = zext i1 %6 to i32
  ret i32 %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.Object* @newObject() #0 {
  %1 = alloca %struct.Object*, align 8
  %2 = call i8* @malloc(i64 24) #6
  %3 = bitcast i8* %2 to %struct.Object*
  store %struct.Object* %3, %struct.Object** %1, align 8
  %4 = load %struct.Object*, %struct.Object** %1, align 8
  %5 = icmp ne %struct.Object* %4, null
  %6 = xor i1 %5, true
  %7 = zext i1 %6 to i32
  %8 = sext i32 %7 to i64
  %9 = icmp ne i64 %8, 0
  br i1 %9, label %10, label %12

10:                                               ; preds = %0
  call void @__assert_rtn(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @__func__.newObject, i64 0, i64 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i64 0, i64 0), i32 157, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i64 0, i64 0)) #7
  unreachable

11:                                               ; No predecessors!
  br label %13

12:                                               ; preds = %0
  br label %13

13:                                               ; preds = %12, %11
  %14 = load %struct.Object*, %struct.Object** %1, align 8
  %15 = getelementptr inbounds %struct.Object, %struct.Object* %14, i32 0, i32 0
  call void @initHeader(%struct.header* %15, i32 -6)
  %16 = load %struct.Object*, %struct.Object** %1, align 8
  %17 = getelementptr inbounds %struct.Object, %struct.Object* %16, i32 0, i32 1
  store %struct.ObjectVTable* @ObjectVTTemplate, %struct.ObjectVTable** %17, align 8
  %18 = load %struct.Object*, %struct.Object** %1, align 8
  ret %struct.Object* %18
}

; Function Attrs: allocsize(0)
declare i8* @malloc(i64) #1

; Function Attrs: cold noreturn
declare void @__assert_rtn(i8*, i8*, i32, i8*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @initHeader(%struct.header* %0, i32 %1) #0 {
  %3 = alloca %struct.header*, align 8
  %4 = alloca i32, align 4
  store %struct.header* %0, %struct.header** %3, align 8
  store i32 %1, i32* %4, align 4
  %5 = load %struct.header*, %struct.header** %3, align 8
  %6 = getelementptr inbounds %struct.header, %struct.header* %5, i32 0, i32 0
  store i64 0, i64* %6, align 8
  %7 = load i32, i32* %4, align 4
  %8 = load %struct.header*, %struct.header** %3, align 8
  %9 = getelementptr inbounds %struct.header, %struct.header* %8, i32 0, i32 1
  store i32 %7, i32* %9, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.Nothing* @newNothing() #0 {
  ret %struct.Nothing* @Nothing
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.Boolean* @newBoolean(i64 %0) #0 {
  %2 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  %3 = load i64, i64* %2, align 8
  %4 = icmp eq i64 %3, 1
  %5 = zext i1 %4 to i64
  %6 = select i1 %4, %struct.Boolean* @True, %struct.Boolean* @False
  ret %struct.Boolean* %6
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.Integer* @newInteger(i64 %0) #0 {
  %2 = alloca i64, align 8
  %3 = alloca %struct.Integer*, align 8
  store i64 %0, i64* %2, align 8
  %4 = call i8* @malloc(i64 32) #6
  %5 = bitcast i8* %4 to %struct.Integer*
  store %struct.Integer* %5, %struct.Integer** %3, align 8
  %6 = load %struct.Integer*, %struct.Integer** %3, align 8
  %7 = icmp ne %struct.Integer* %6, null
  %8 = xor i1 %7, true
  %9 = zext i1 %8 to i32
  %10 = sext i32 %9 to i64
  %11 = icmp ne i64 %10, 0
  br i1 %11, label %12, label %14

12:                                               ; preds = %1
  call void @__assert_rtn(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @__func__.newInteger, i64 0, i64 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i64 0, i64 0), i32 225, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i64 0, i64 0)) #7
  unreachable

13:                                               ; No predecessors!
  br label %15

14:                                               ; preds = %1
  br label %15

15:                                               ; preds = %14, %13
  %16 = load %struct.Integer*, %struct.Integer** %3, align 8
  %17 = getelementptr inbounds %struct.Integer, %struct.Integer* %16, i32 0, i32 0
  call void @initHeader(%struct.header* %17, i32 -5)
  %18 = load %struct.Integer*, %struct.Integer** %3, align 8
  %19 = getelementptr inbounds %struct.Integer, %struct.Integer* %18, i32 0, i32 1
  store %struct.IntegerVTable* @IntegerVTTemplate, %struct.IntegerVTable** %19, align 8
  %20 = load i64, i64* %2, align 8
  %21 = load %struct.Integer*, %struct.Integer** %3, align 8
  %22 = getelementptr inbounds %struct.Integer, %struct.Integer* %21, i32 0, i32 2
  store i64 %20, i64* %22, align 8
  %23 = load %struct.Integer*, %struct.Integer** %3, align 8
  ret %struct.Integer* %23
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.Float* @newFloat(double %0) #0 {
  %2 = alloca double, align 8
  %3 = alloca %struct.Float*, align 8
  store double %0, double* %2, align 8
  %4 = call i8* @malloc(i64 32) #6
  %5 = bitcast i8* %4 to %struct.Float*
  store %struct.Float* %5, %struct.Float** %3, align 8
  %6 = load %struct.Float*, %struct.Float** %3, align 8
  %7 = icmp ne %struct.Float* %6, null
  %8 = xor i1 %7, true
  %9 = zext i1 %8 to i32
  %10 = sext i32 %9 to i64
  %11 = icmp ne i64 %10, 0
  br i1 %11, label %12, label %14

12:                                               ; preds = %1
  call void @__assert_rtn(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @__func__.newFloat, i64 0, i64 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i64 0, i64 0), i32 265, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i64 0, i64 0)) #7
  unreachable

13:                                               ; No predecessors!
  br label %15

14:                                               ; preds = %1
  br label %15

15:                                               ; preds = %14, %13
  %16 = load %struct.Float*, %struct.Float** %3, align 8
  %17 = getelementptr inbounds %struct.Float, %struct.Float* %16, i32 0, i32 0
  call void @initHeader(%struct.header* %17, i32 -4)
  %18 = load %struct.Float*, %struct.Float** %3, align 8
  %19 = getelementptr inbounds %struct.Float, %struct.Float* %18, i32 0, i32 1
  store %struct.FloatVTable* @FloatVTTemplate, %struct.FloatVTable** %19, align 8
  %20 = load double, double* %2, align 8
  %21 = load %struct.Float*, %struct.Float** %3, align 8
  %22 = getelementptr inbounds %struct.Float, %struct.Float* %21, i32 0, i32 2
  store double %20, double* %22, align 8
  %23 = load %struct.Float*, %struct.Float** %3, align 8
  ret %struct.Float* %23
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define dso_local %struct.String* @newString(i8* %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct.String*, align 8
  store i8* %0, i8** %2, align 8
  %4 = call i8* @malloc(i64 32) #6
  %5 = bitcast i8* %4 to %struct.String*
  store %struct.String* %5, %struct.String** %3, align 8
  %6 = load %struct.String*, %struct.String** %3, align 8
  %7 = icmp ne %struct.String* %6, null
  %8 = xor i1 %7, true
  %9 = zext i1 %8 to i32
  %10 = sext i32 %9 to i64
  %11 = icmp ne i64 %10, 0
  br i1 %11, label %12, label %14

12:                                               ; preds = %1
  call void @__assert_rtn(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @__func__.newString, i64 0, i64 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i64 0, i64 0), i32 301, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i64 0, i64 0)) #7
  unreachable

13:                                               ; No predecessors!
  br label %15

14:                                               ; preds = %1
  br label %15

15:                                               ; preds = %14, %13
  %16 = load %struct.String*, %struct.String** %3, align 8
  %17 = getelementptr inbounds %struct.String, %struct.String* %16, i32 0, i32 0
  call void @initHeader(%struct.header* %17, i32 -2)
  %18 = load %struct.String*, %struct.String** %3, align 8
  %19 = getelementptr inbounds %struct.String, %struct.String* %18, i32 0, i32 1
  store %struct.StringVTable* @StringVTTemplate, %struct.StringVTable** %19, align 8
  %20 = load i8*, i8** %2, align 8
  %21 = call i8* @strdup(i8* %20)
  %22 = load %struct.String*, %struct.String** %3, align 8
  %23 = getelementptr inbounds %struct.String, %struct.String* %22, i32 0, i32 2
  store i8* %21, i8** %23, align 8
  %24 = load %struct.String*, %struct.String** %3, align 8
  ret %struct.String* %24
}

declare i8* @strdup(i8*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Boolean* @equalsObject(%struct.Object* %0, %struct.Object* %1) #0 {
  %3 = alloca %struct.Object*, align 8
  %4 = alloca %struct.Object*, align 8
  store %struct.Object* %0, %struct.Object** %3, align 8
  store %struct.Object* %1, %struct.Object** %4, align 8
  %5 = load %struct.Object*, %struct.Object** %3, align 8
  %6 = load %struct.Object*, %struct.Object** %4, align 8
  %7 = icmp eq %struct.Object* %5, %6
  %8 = zext i1 %7 to i64
  %9 = select i1 %7, %struct.Boolean* @True, %struct.Boolean* @False
  ret %struct.Boolean* %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Nothing* @printObject(%struct.Object* %0) #0 {
  %2 = alloca %struct.Object*, align 8
  store %struct.Object* %0, %struct.Object** %2, align 8
  %3 = load %struct.Object*, %struct.Object** %2, align 8
  %4 = ptrtoint %struct.Object* %3 to i64
  %5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.3, i64 0, i64 0), i64 %4)
  ret %struct.Nothing* @Nothing
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Nothing* @destroyObject(%struct.Object* %0) #0 {
  %2 = alloca %struct.Object*, align 8
  store %struct.Object* %0, %struct.Object** %2, align 8
  %3 = load %struct.Object*, %struct.Object** %2, align 8
  %4 = call i32 @decrementRefCounter(%struct.Object* %3)
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %6, label %9

6:                                                ; preds = %1
  %7 = load %struct.Object*, %struct.Object** %2, align 8
  %8 = bitcast %struct.Object* %7 to i8*
  call void @free(i8* %8)
  br label %9

9:                                                ; preds = %6, %1
  ret %struct.Nothing* @Nothing
}

declare i32 @printf(i8*, ...) #3

declare void @free(i8*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Boolean* @equalsNothing(%struct.Nothing* %0, %struct.Nothing* %1) #0 {
  %3 = alloca %struct.Nothing*, align 8
  %4 = alloca %struct.Nothing*, align 8
  store %struct.Nothing* %0, %struct.Nothing** %3, align 8
  store %struct.Nothing* %1, %struct.Nothing** %4, align 8
  %5 = load %struct.Nothing*, %struct.Nothing** %3, align 8
  %6 = getelementptr inbounds %struct.Nothing, %struct.Nothing* %5, i32 0, i32 0
  %7 = getelementptr inbounds %struct.header, %struct.header* %6, i32 0, i32 1
  %8 = load i32, i32* %7, align 8
  %9 = load %struct.Nothing*, %struct.Nothing** %4, align 8
  %10 = getelementptr inbounds %struct.Nothing, %struct.Nothing* %9, i32 0, i32 0
  %11 = getelementptr inbounds %struct.header, %struct.header* %10, i32 0, i32 1
  %12 = load i32, i32* %11, align 8
  %13 = icmp eq i32 %8, %12
  br i1 %13, label %14, label %20

14:                                               ; preds = %2
  %15 = load %struct.Nothing*, %struct.Nothing** %3, align 8
  %16 = getelementptr inbounds %struct.Nothing, %struct.Nothing* %15, i32 0, i32 0
  %17 = getelementptr inbounds %struct.header, %struct.header* %16, i32 0, i32 1
  %18 = load i32, i32* %17, align 8
  %19 = icmp eq i32 %18, -1
  br label %20

20:                                               ; preds = %14, %2
  %21 = phi i1 [ false, %2 ], [ %19, %14 ]
  %22 = zext i1 %21 to i64
  %23 = select i1 %21, %struct.Boolean* @True, %struct.Boolean* @False
  ret %struct.Boolean* %23
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Nothing* @printNothing(%struct.Nothing* %0) #0 {
  %2 = alloca %struct.Nothing*, align 8
  store %struct.Nothing* %0, %struct.Nothing** %2, align 8
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.4, i64 0, i64 0))
  ret %struct.Nothing* @Nothing
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Nothing* @destroyNothing(%struct.Nothing* %0) #0 {
  %2 = alloca %struct.Nothing*, align 8
  store %struct.Nothing* %0, %struct.Nothing** %2, align 8
  ret %struct.Nothing* @Nothing
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Boolean* @equalsBoolean(%struct.Boolean* %0, %struct.Boolean* %1) #0 {
  %3 = alloca %struct.Boolean*, align 8
  %4 = alloca %struct.Boolean*, align 8
  store %struct.Boolean* %0, %struct.Boolean** %3, align 8
  store %struct.Boolean* %1, %struct.Boolean** %4, align 8
  %5 = load %struct.Boolean*, %struct.Boolean** %3, align 8
  %6 = getelementptr inbounds %struct.Boolean, %struct.Boolean* %5, i32 0, i32 2
  %7 = load i64, i64* %6, align 8
  %8 = load %struct.Boolean*, %struct.Boolean** %4, align 8
  %9 = getelementptr inbounds %struct.Boolean, %struct.Boolean* %8, i32 0, i32 2
  %10 = load i64, i64* %9, align 8
  %11 = icmp eq i64 %7, %10
  %12 = zext i1 %11 to i64
  %13 = select i1 %11, %struct.Boolean* @True, %struct.Boolean* @False
  ret %struct.Boolean* %13
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Nothing* @printBoolean(%struct.Boolean* %0) #0 {
  %2 = alloca %struct.Boolean*, align 8
  store %struct.Boolean* %0, %struct.Boolean** %2, align 8
  %3 = load %struct.Boolean*, %struct.Boolean** %2, align 8
  %4 = call i32 @isTrue(%struct.Boolean* %3)
  %5 = icmp ne i32 %4, 0
  br i1 %5, label %6, label %8

6:                                                ; preds = %1
  %7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.5, i64 0, i64 0))
  br label %10

8:                                                ; preds = %1
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i64 0, i64 0))
  br label %10

10:                                               ; preds = %8, %6
  %11 = phi i32 [ %7, %6 ], [ %9, %8 ]
  ret %struct.Nothing* @Nothing
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Nothing* @destroyBoolean(%struct.Boolean* %0) #0 {
  %2 = alloca %struct.Boolean*, align 8
  store %struct.Boolean* %0, %struct.Boolean** %2, align 8
  ret %struct.Nothing* @Nothing
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Boolean* @equalsInteger(%struct.Integer* %0, %struct.Integer* %1) #0 {
  %3 = alloca %struct.Integer*, align 8
  %4 = alloca %struct.Integer*, align 8
  store %struct.Integer* %0, %struct.Integer** %3, align 8
  store %struct.Integer* %1, %struct.Integer** %4, align 8
  %5 = load %struct.Integer*, %struct.Integer** %3, align 8
  %6 = getelementptr inbounds %struct.Integer, %struct.Integer* %5, i32 0, i32 2
  %7 = load i64, i64* %6, align 8
  %8 = load %struct.Integer*, %struct.Integer** %4, align 8
  %9 = getelementptr inbounds %struct.Integer, %struct.Integer* %8, i32 0, i32 2
  %10 = load i64, i64* %9, align 8
  %11 = icmp eq i64 %7, %10
  %12 = zext i1 %11 to i64
  %13 = select i1 %11, %struct.Boolean* @True, %struct.Boolean* @False
  ret %struct.Boolean* %13
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Nothing* @printInteger(%struct.Integer* %0) #0 {
  %2 = alloca %struct.Integer*, align 8
  store %struct.Integer* %0, %struct.Integer** %2, align 8
  %3 = load %struct.Integer*, %struct.Integer** %2, align 8
  %4 = getelementptr inbounds %struct.Integer, %struct.Integer* %3, i32 0, i32 2
  %5 = load i64, i64* %4, align 8
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.7, i64 0, i64 0), i64 %5)
  ret %struct.Nothing* @Nothing
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Integer* @addInteger(%struct.Integer* %0, %struct.Integer* %1) #0 {
  %3 = alloca %struct.Integer*, align 8
  %4 = alloca %struct.Integer*, align 8
  store %struct.Integer* %0, %struct.Integer** %3, align 8
  store %struct.Integer* %1, %struct.Integer** %4, align 8
  %5 = load %struct.Integer*, %struct.Integer** %3, align 8
  %6 = getelementptr inbounds %struct.Integer, %struct.Integer* %5, i32 0, i32 2
  %7 = load i64, i64* %6, align 8
  %8 = load %struct.Integer*, %struct.Integer** %4, align 8
  %9 = getelementptr inbounds %struct.Integer, %struct.Integer* %8, i32 0, i32 2
  %10 = load i64, i64* %9, align 8
  %11 = add nsw i64 %7, %10
  %12 = call %struct.Integer* @newInteger(i64 %11)
  ret %struct.Integer* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Integer* @mulInteger(%struct.Integer* %0, %struct.Integer* %1) #0 {
  %3 = alloca %struct.Integer*, align 8
  %4 = alloca %struct.Integer*, align 8
  store %struct.Integer* %0, %struct.Integer** %3, align 8
  store %struct.Integer* %1, %struct.Integer** %4, align 8
  %5 = load %struct.Integer*, %struct.Integer** %3, align 8
  %6 = getelementptr inbounds %struct.Integer, %struct.Integer* %5, i32 0, i32 2
  %7 = load i64, i64* %6, align 8
  %8 = load %struct.Integer*, %struct.Integer** %4, align 8
  %9 = getelementptr inbounds %struct.Integer, %struct.Integer* %8, i32 0, i32 2
  %10 = load i64, i64* %9, align 8
  %11 = mul nsw i64 %7, %10
  %12 = call %struct.Integer* @newInteger(i64 %11)
  ret %struct.Integer* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Integer* @subInteger(%struct.Integer* %0, %struct.Integer* %1) #0 {
  %3 = alloca %struct.Integer*, align 8
  %4 = alloca %struct.Integer*, align 8
  store %struct.Integer* %0, %struct.Integer** %3, align 8
  store %struct.Integer* %1, %struct.Integer** %4, align 8
  %5 = load %struct.Integer*, %struct.Integer** %3, align 8
  %6 = getelementptr inbounds %struct.Integer, %struct.Integer* %5, i32 0, i32 2
  %7 = load i64, i64* %6, align 8
  %8 = load %struct.Integer*, %struct.Integer** %4, align 8
  %9 = getelementptr inbounds %struct.Integer, %struct.Integer* %8, i32 0, i32 2
  %10 = load i64, i64* %9, align 8
  %11 = sub nsw i64 %7, %10
  %12 = call %struct.Integer* @newInteger(i64 %11)
  ret %struct.Integer* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Integer* @divInteger(%struct.Integer* %0, %struct.Integer* %1) #0 {
  %3 = alloca %struct.Integer*, align 8
  %4 = alloca %struct.Integer*, align 8
  store %struct.Integer* %0, %struct.Integer** %3, align 8
  store %struct.Integer* %1, %struct.Integer** %4, align 8
  %5 = load %struct.Integer*, %struct.Integer** %3, align 8
  %6 = getelementptr inbounds %struct.Integer, %struct.Integer* %5, i32 0, i32 2
  %7 = load i64, i64* %6, align 8
  %8 = load %struct.Integer*, %struct.Integer** %4, align 8
  %9 = getelementptr inbounds %struct.Integer, %struct.Integer* %8, i32 0, i32 2
  %10 = load i64, i64* %9, align 8
  %11 = sdiv i64 %7, %10
  %12 = call %struct.Integer* @newInteger(i64 %11)
  ret %struct.Integer* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Integer* @modInteger(%struct.Integer* %0, %struct.Integer* %1) #0 {
  %3 = alloca %struct.Integer*, align 8
  %4 = alloca %struct.Integer*, align 8
  store %struct.Integer* %0, %struct.Integer** %3, align 8
  store %struct.Integer* %1, %struct.Integer** %4, align 8
  %5 = load %struct.Integer*, %struct.Integer** %3, align 8
  %6 = getelementptr inbounds %struct.Integer, %struct.Integer* %5, i32 0, i32 2
  %7 = load i64, i64* %6, align 8
  %8 = load %struct.Integer*, %struct.Integer** %4, align 8
  %9 = getelementptr inbounds %struct.Integer, %struct.Integer* %8, i32 0, i32 2
  %10 = load i64, i64* %9, align 8
  %11 = srem i64 %7, %10
  %12 = call %struct.Integer* @newInteger(i64 %11)
  ret %struct.Integer* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Boolean* @equalsFloat(%struct.Float* %0, %struct.Float* %1) #0 {
  %3 = alloca %struct.Float*, align 8
  %4 = alloca %struct.Float*, align 8
  store %struct.Float* %0, %struct.Float** %3, align 8
  store %struct.Float* %1, %struct.Float** %4, align 8
  %5 = load %struct.Float*, %struct.Float** %3, align 8
  %6 = getelementptr inbounds %struct.Float, %struct.Float* %5, i32 0, i32 2
  %7 = load double, double* %6, align 8
  %8 = load %struct.Float*, %struct.Float** %4, align 8
  %9 = getelementptr inbounds %struct.Float, %struct.Float* %8, i32 0, i32 2
  %10 = load double, double* %9, align 8
  %11 = fcmp oeq double %7, %10
  %12 = zext i1 %11 to i64
  %13 = select i1 %11, %struct.Boolean* @True, %struct.Boolean* @False
  ret %struct.Boolean* %13
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Nothing* @printFloat(%struct.Float* %0) #0 {
  %2 = alloca %struct.Float*, align 8
  store %struct.Float* %0, %struct.Float** %2, align 8
  %3 = load %struct.Float*, %struct.Float** %2, align 8
  %4 = getelementptr inbounds %struct.Float, %struct.Float* %3, i32 0, i32 2
  %5 = load double, double* %4, align 8
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i64 0, i64 0), double %5)
  ret %struct.Nothing* @Nothing
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Float* @addFloat(%struct.Float* %0, %struct.Float* %1) #0 {
  %3 = alloca %struct.Float*, align 8
  %4 = alloca %struct.Float*, align 8
  store %struct.Float* %0, %struct.Float** %3, align 8
  store %struct.Float* %1, %struct.Float** %4, align 8
  %5 = load %struct.Float*, %struct.Float** %3, align 8
  %6 = getelementptr inbounds %struct.Float, %struct.Float* %5, i32 0, i32 2
  %7 = load double, double* %6, align 8
  %8 = load %struct.Float*, %struct.Float** %4, align 8
  %9 = getelementptr inbounds %struct.Float, %struct.Float* %8, i32 0, i32 2
  %10 = load double, double* %9, align 8
  %11 = fadd double %7, %10
  %12 = call %struct.Float* @newFloat(double %11)
  ret %struct.Float* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Float* @mulFloat(%struct.Float* %0, %struct.Float* %1) #0 {
  %3 = alloca %struct.Float*, align 8
  %4 = alloca %struct.Float*, align 8
  store %struct.Float* %0, %struct.Float** %3, align 8
  store %struct.Float* %1, %struct.Float** %4, align 8
  %5 = load %struct.Float*, %struct.Float** %3, align 8
  %6 = getelementptr inbounds %struct.Float, %struct.Float* %5, i32 0, i32 2
  %7 = load double, double* %6, align 8
  %8 = load %struct.Float*, %struct.Float** %4, align 8
  %9 = getelementptr inbounds %struct.Float, %struct.Float* %8, i32 0, i32 2
  %10 = load double, double* %9, align 8
  %11 = fmul double %7, %10
  %12 = call %struct.Float* @newFloat(double %11)
  ret %struct.Float* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Float* @subFloat(%struct.Float* %0, %struct.Float* %1) #0 {
  %3 = alloca %struct.Float*, align 8
  %4 = alloca %struct.Float*, align 8
  store %struct.Float* %0, %struct.Float** %3, align 8
  store %struct.Float* %1, %struct.Float** %4, align 8
  %5 = load %struct.Float*, %struct.Float** %3, align 8
  %6 = getelementptr inbounds %struct.Float, %struct.Float* %5, i32 0, i32 2
  %7 = load double, double* %6, align 8
  %8 = load %struct.Float*, %struct.Float** %4, align 8
  %9 = getelementptr inbounds %struct.Float, %struct.Float* %8, i32 0, i32 2
  %10 = load double, double* %9, align 8
  %11 = fsub double %7, %10
  %12 = call %struct.Float* @newFloat(double %11)
  ret %struct.Float* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Float* @divFloat(%struct.Float* %0, %struct.Float* %1) #0 {
  %3 = alloca %struct.Float*, align 8
  %4 = alloca %struct.Float*, align 8
  store %struct.Float* %0, %struct.Float** %3, align 8
  store %struct.Float* %1, %struct.Float** %4, align 8
  %5 = load %struct.Float*, %struct.Float** %3, align 8
  %6 = getelementptr inbounds %struct.Float, %struct.Float* %5, i32 0, i32 2
  %7 = load double, double* %6, align 8
  %8 = load %struct.Float*, %struct.Float** %4, align 8
  %9 = getelementptr inbounds %struct.Float, %struct.Float* %8, i32 0, i32 2
  %10 = load double, double* %9, align 8
  %11 = fdiv double %7, %10
  %12 = call %struct.Float* @newFloat(double %11)
  ret %struct.Float* %12
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Boolean* @equalsString(%struct.String* %0, %struct.String* %1) #0 {
  %3 = alloca %struct.String*, align 8
  %4 = alloca %struct.String*, align 8
  %5 = alloca i32, align 4
  store %struct.String* %0, %struct.String** %3, align 8
  store %struct.String* %1, %struct.String** %4, align 8
  %6 = load %struct.String*, %struct.String** %3, align 8
  %7 = getelementptr inbounds %struct.String, %struct.String* %6, i32 0, i32 2
  %8 = load i8*, i8** %7, align 8
  %9 = load %struct.String*, %struct.String** %4, align 8
  %10 = getelementptr inbounds %struct.String, %struct.String* %9, i32 0, i32 2
  %11 = load i8*, i8** %10, align 8
  %12 = call i32 @strcmp(i8* %8, i8* %11)
  store i32 %12, i32* %5, align 4
  %13 = load i32, i32* %5, align 4
  %14 = icmp eq i32 %13, 0
  %15 = zext i1 %14 to i64
  %16 = select i1 %14, %struct.Boolean* @True, %struct.Boolean* @False
  ret %struct.Boolean* %16
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Nothing* @printString(%struct.String* %0) #0 {
  %2 = alloca %struct.String*, align 8
  store %struct.String* %0, %struct.String** %2, align 8
  %3 = load %struct.__sFILE*, %struct.__sFILE** @__stdoutp, align 8
  %4 = load %struct.String*, %struct.String** %2, align 8
  %5 = getelementptr inbounds %struct.String, %struct.String* %4, i32 0, i32 2
  %6 = load i8*, i8** %5, align 8
  %7 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %3, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.9, i64 0, i64 0), i8* %6)
  ret %struct.Nothing* @Nothing
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.Nothing* @destroyString(%struct.String* %0) #0 {
  %2 = alloca %struct.String*, align 8
  store %struct.String* %0, %struct.String** %2, align 8
  %3 = load %struct.String*, %struct.String** %2, align 8
  %4 = bitcast %struct.String* %3 to %struct.Object*
  %5 = call i32 @decrementRefCounter(%struct.Object* %4)
  %6 = icmp ne i32 %5, 0
  br i1 %6, label %7, label %13

7:                                                ; preds = %1
  %8 = load %struct.String*, %struct.String** %2, align 8
  %9 = getelementptr inbounds %struct.String, %struct.String* %8, i32 0, i32 2
  %10 = load i8*, i8** %9, align 8
  call void @free(i8* %10)
  %11 = load %struct.String*, %struct.String** %2, align 8
  %12 = bitcast %struct.String* %11 to i8*
  call void @free(i8* %12)
  br label %13

13:                                               ; preds = %7, %1
  ret %struct.Nothing* @Nothing
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal %struct.String* @addString(%struct.String* %0, %struct.String* %1) #0 {
  %3 = alloca %struct.String*, align 8
  %4 = alloca %struct.String*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca %struct.String*, align 8
  store %struct.String* %0, %struct.String** %3, align 8
  store %struct.String* %1, %struct.String** %4, align 8
  %10 = load %struct.String*, %struct.String** %3, align 8
  %11 = getelementptr inbounds %struct.String, %struct.String* %10, i32 0, i32 2
  %12 = load i8*, i8** %11, align 8
  %13 = call i64 @strlen(i8* %12)
  %14 = trunc i64 %13 to i32
  store i32 %14, i32* %5, align 4
  %15 = load %struct.String*, %struct.String** %4, align 8
  %16 = getelementptr inbounds %struct.String, %struct.String* %15, i32 0, i32 2
  %17 = load i8*, i8** %16, align 8
  %18 = call i64 @strlen(i8* %17)
  %19 = trunc i64 %18 to i32
  store i32 %19, i32* %6, align 4
  %20 = load i32, i32* %5, align 4
  %21 = load i32, i32* %6, align 4
  %22 = add nsw i32 %20, %21
  store i32 %22, i32* %7, align 4
  %23 = load i32, i32* %7, align 4
  %24 = add nsw i32 %23, 1
  %25 = sext i32 %24 to i64
  %26 = call i8* @malloc(i64 %25) #6
  store i8* %26, i8** %8, align 8
  %27 = load i8*, i8** %8, align 8
  %28 = icmp ne i8* %27, null
  %29 = xor i1 %28, true
  %30 = zext i1 %29 to i32
  %31 = sext i32 %30 to i64
  %32 = icmp ne i64 %31, 0
  br i1 %32, label %33, label %35

33:                                               ; preds = %2
  call void @__assert_rtn(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @__func__.addString, i64 0, i64 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i64 0, i64 0), i32 332, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.10, i64 0, i64 0)) #7
  unreachable

34:                                               ; No predecessors!
  br label %36

35:                                               ; preds = %2
  br label %36

36:                                               ; preds = %35, %34
  %37 = load i8*, i8** %8, align 8
  %38 = load %struct.String*, %struct.String** %3, align 8
  %39 = getelementptr inbounds %struct.String, %struct.String* %38, i32 0, i32 2
  %40 = load i8*, i8** %39, align 8
  %41 = load i32, i32* %5, align 4
  %42 = sext i32 %41 to i64
  %43 = load i8*, i8** %8, align 8
  %44 = call i64 @llvm.objectsize.i64.p0i8(i8* %43, i1 false, i1 true, i1 false)
  %45 = call i8* @__strncpy_chk(i8* %37, i8* %40, i64 %42, i64 %44) #8
  %46 = load i8*, i8** %8, align 8
  %47 = load i32, i32* %5, align 4
  %48 = sext i32 %47 to i64
  %49 = getelementptr inbounds i8, i8* %46, i64 %48
  %50 = load %struct.String*, %struct.String** %4, align 8
  %51 = getelementptr inbounds %struct.String, %struct.String* %50, i32 0, i32 2
  %52 = load i8*, i8** %51, align 8
  %53 = load i32, i32* %6, align 4
  %54 = sext i32 %53 to i64
  %55 = load i8*, i8** %8, align 8
  %56 = load i32, i32* %5, align 4
  %57 = sext i32 %56 to i64
  %58 = getelementptr inbounds i8, i8* %55, i64 %57
  %59 = call i64 @llvm.objectsize.i64.p0i8(i8* %58, i1 false, i1 true, i1 false)
  %60 = call i8* @__strncpy_chk(i8* %49, i8* %52, i64 %54, i64 %59) #8
  %61 = load i8*, i8** %8, align 8
  %62 = load i32, i32* %7, align 4
  %63 = sext i32 %62 to i64
  %64 = getelementptr inbounds i8, i8* %61, i64 %63
  store i8 0, i8* %64, align 1
  %65 = call i8* @malloc(i64 32) #6
  %66 = bitcast i8* %65 to %struct.String*
  store %struct.String* %66, %struct.String** %9, align 8
  %67 = load %struct.String*, %struct.String** %9, align 8
  %68 = icmp ne %struct.String* %67, null
  %69 = xor i1 %68, true
  %70 = zext i1 %69 to i32
  %71 = sext i32 %70 to i64
  %72 = icmp ne i64 %71, 0
  br i1 %72, label %73, label %75

73:                                               ; preds = %36
  call void @__assert_rtn(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @__func__.addString, i64 0, i64 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str, i64 0, i64 0), i32 337, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i64 0, i64 0)) #7
  unreachable

74:                                               ; No predecessors!
  br label %76

75:                                               ; preds = %36
  br label %76

76:                                               ; preds = %75, %74
  %77 = load %struct.String*, %struct.String** %9, align 8
  %78 = getelementptr inbounds %struct.String, %struct.String* %77, i32 0, i32 0
  call void @initHeader(%struct.header* %78, i32 -2)
  %79 = load %struct.String*, %struct.String** %9, align 8
  %80 = getelementptr inbounds %struct.String, %struct.String* %79, i32 0, i32 1
  store %struct.StringVTable* @StringVTTemplate, %struct.StringVTable** %80, align 8
  %81 = load i8*, i8** %8, align 8
  %82 = load %struct.String*, %struct.String** %9, align 8
  %83 = getelementptr inbounds %struct.String, %struct.String* %82, i32 0, i32 2
  store i8* %81, i8** %83, align 8
  %84 = load %struct.String*, %struct.String** %9, align 8
  ret %struct.String* %84
}

declare i32 @strcmp(i8*, i8*) #3

declare i32 @fprintf(%struct.__sFILE*, i8*, ...) #3

declare i64 @strlen(i8*) #3

; Function Attrs: nounwind
declare i8* @__strncpy_chk(i8*, i8*, i64, i64) #4

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare i64 @llvm.objectsize.i64.p0i8(i8*, i1 immarg, i1 immarg, i1 immarg) #5

attributes #0 = { noinline nounwind optnone ssp uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { allocsize(0) "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { cold noreturn "disable-tail-calls"="true" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #6 = { allocsize(0) }
attributes #7 = { cold noreturn }
attributes #8 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 12.0.0"}
