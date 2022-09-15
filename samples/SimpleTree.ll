; ModuleID = '../samples/SimpleTree.qk'
source_filename = "../samples/SimpleTree.qk"

%Object_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Object*)*, void (%Object*)* }
%Object = type { %Object_vtable* }
%String = type { %String_vtable*, i8* }
%String_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%String*)*, void (%String*)*, i8 (%String*, %String*)*, i8 (%String*, %String*)*, %String* (%String*, %String*)* }
%Node_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Object*)*, void (%Object*)*, %Nothing* (%Node*)* }
%Nothing = type { %Nothing_vtable* }
%Nothing_vtable = type { %Object_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Nothing*)*, void (%Nothing*)*, i8 (%Nothing*, %Nothing*)*, i8 (%Nothing*, %Nothing*)* }
%Node = type { %Node_vtable*, %Object* }
%LeafNode_vtable = type { %Node_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Object*)*, void (%Object*)*, %Nothing* (%Node*)* }
%BinNode_vtable = type { %Node_vtable*, i8 (%Object*, %Object*)*, i8 (%Object*, %Object*)*, %String* (%Object*)*, void (%Object*)*, %Nothing* (%BinNode*)* }
%BinNode = type { %BinNode_vtable*, %Object*, %Node*, %Node* }
%LeafNode = type { %LeafNode_vtable*, %Object* }

@ObjectVtable = external global %Object_vtable
@NodeVtable = internal constant %Node_vtable { %Object_vtable* @ObjectVtable, i8 (%Object*, %Object*)* @Object__eq__Object, i8 (%Object*, %Object*)* @Object__ne__Object, %String* (%Object*)* @Object__str__, void (%Object*)* @Object__del__, %Nothing* (%Node*)* @NodeprintTree }
@0 = private unnamed_addr constant [5 x i8] c"%s \0A\00", align 1
@LeafNodeVtable = internal constant %LeafNode_vtable { %Node_vtable* @NodeVtable, i8 (%Object*, %Object*)* @Object__eq__Object, i8 (%Object*, %Object*)* @Object__ne__Object, %String* (%Object*)* @Object__str__, void (%Object*)* @Object__del__, %Nothing* (%Node*)* @NodeprintTree }
@BinNodeVtable = internal constant %BinNode_vtable { %Node_vtable* @NodeVtable, i8 (%Object*, %Object*)* @Object__eq__Object, i8 (%Object*, %Object*)* @Object__ne__Object, %String* (%Object*)* @Object__str__, void (%Object*)* @Object__del__, %Nothing* (%BinNode*)* @BinNodeprintTree }
@1 = private unnamed_addr constant [5 x i8] c"%s \0A\00", align 1
@2 = private unnamed_addr constant [2 x i8] c"2\00", align 1
@3 = private unnamed_addr constant [2 x i8] c"1\00", align 1
@4 = private unnamed_addr constant [2 x i8] c"3\00", align 1

declare %Object* @Object_create()

declare %String* @String_create(i8*)

declare %Nothing* @Nothing_create()

define dso_local %Node* @Node_create(%Object* %0) {
Node_create:
  %1 = call i8* @malloc(i64 16)
  %2 = bitcast i8* %1 to %Node*
  %3 = getelementptr inbounds %Node, %Node* %2, i32 0, i32 0
  store %Node_vtable* @NodeVtable, %Node_vtable** %3
  call void @Node_init(%Node* %2, %Object* %0)
  ret %Node* %2
}

declare %Node* @Object_init(%Node*, %Object*)

define dso_local void @Node_init(%Node* %0, %Object* %1) {
Node_init:
  %2 = alloca %Node*
  store %Node* %0, %Node** %2
  %3 = alloca %Object*
  store %Object* %1, %Object** %3
  %4 = load %Object*, %Object** %3, align 8
  %5 = load %Node*, %Node** %2, align 8
  %6 = getelementptr inbounds %Node, %Node* %5, i32 0, i32 1
  store %Object* %4, %Object** %6
  ret void
}

declare i8* @malloc(i64)

declare void @Object__del__(%Object*)

declare %String* @Object__str__(%Object*)

declare i8 @Object__ne__Object(%Object*, %Object*)

declare i8 @Object__eq__Object(%Object*, %Object*)

define %Nothing* @NodeprintTree(%Node* %0) {
NodeprintTree:
  %1 = alloca %Node*
  store %Node* %0, %Node** %1
  %2 = load %Node*, %Node** %1, align 8
  %3 = getelementptr inbounds %Node, %Node* %2, i32 0, i32 1
  %4 = load %Object*, %Object** %3
  %5 = getelementptr inbounds %Object, %Object* %4, i32 0, i32 0
  %6 = load %Object_vtable*, %Object_vtable** %5
  %7 = getelementptr inbounds %Object_vtable, %Object_vtable* %6, i32 0, i32 3
  %8 = load %String* (%Object*)*, %String* (%Object*)** %7
  %9 = call %String* %8(%Object* %4)
  %10 = call i8* @String_getData(%String* %9)
  %11 = call i32 (...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i32 0, i32 0), i8* %10)
  %12 = call %Nothing* @Nothing_create()
  ret %Nothing* %12
}

declare i32 @printf(...)

declare i8* @String_getData(%String*)

define dso_local %LeafNode* @LeafNode_create(%Object* %0) {
LeafNode_create:
  %1 = call i8* @malloc(i64 16)
  %2 = bitcast i8* %1 to %LeafNode*
  %3 = getelementptr inbounds %LeafNode, %LeafNode* %2, i32 0, i32 0
  store %LeafNode_vtable* @LeafNodeVtable, %LeafNode_vtable** %3
  call void @LeafNode_init(%LeafNode* %2, %Object* %0)
  ret %LeafNode* %2
}

define dso_local void @LeafNode_init(%LeafNode* %0, %Object* %1) {
LeafNode_init:
  %2 = alloca %LeafNode*
  store %LeafNode* %0, %LeafNode** %2
  %3 = alloca %Object*
  store %Object* %1, %Object** %3
  %4 = bitcast %LeafNode* %0 to %Node*
  %5 = load %Object*, %Object** %3, align 8
  call void @Node_init(%Node* %4, %Object* %5)
  ret void
}

define dso_local %BinNode* @BinNode_create(%Object* %0, %Node* %1, %Node* %2) {
BinNode_create:
  %3 = call i8* @malloc(i64 32)
  %4 = bitcast i8* %3 to %BinNode*
  %5 = getelementptr inbounds %BinNode, %BinNode* %4, i32 0, i32 0
  store %BinNode_vtable* @BinNodeVtable, %BinNode_vtable** %5
  call void @BinNode_init(%BinNode* %4, %Object* %0, %Node* %1, %Node* %2)
  ret %BinNode* %4
}

define dso_local void @BinNode_init(%BinNode* %0, %Object* %1, %Node* %2, %Node* %3) {
BinNode_init:
  %4 = alloca %BinNode*
  store %BinNode* %0, %BinNode** %4
  %5 = alloca %Object*
  store %Object* %1, %Object** %5
  %6 = alloca %Node*
  store %Node* %2, %Node** %6
  %7 = alloca %Node*
  store %Node* %3, %Node** %7
  %8 = bitcast %BinNode* %0 to %Node*
  %9 = load %Object*, %Object** %5, align 8
  call void @Node_init(%Node* %8, %Object* %9)
  %10 = load %Node*, %Node** %6, align 8
  %11 = load %BinNode*, %BinNode** %4, align 8
  %12 = getelementptr inbounds %BinNode, %BinNode* %11, i32 0, i32 2
  store %Node* %10, %Node** %12
  %13 = load %Node*, %Node** %7, align 8
  %14 = load %BinNode*, %BinNode** %4, align 8
  %15 = getelementptr inbounds %BinNode, %BinNode* %14, i32 0, i32 3
  store %Node* %13, %Node** %15
  ret void
}

define %Nothing* @BinNodeprintTree(%BinNode* %0) {
BinNodeprintTree:
  %1 = alloca %BinNode*
  store %BinNode* %0, %BinNode** %1
  %2 = load %BinNode*, %BinNode** %1, align 8
  %3 = getelementptr inbounds %BinNode, %BinNode* %2, i32 0, i32 1
  %4 = load %Object*, %Object** %3
  %5 = getelementptr inbounds %Object, %Object* %4, i32 0, i32 0
  %6 = load %Object_vtable*, %Object_vtable** %5
  %7 = getelementptr inbounds %Object_vtable, %Object_vtable* %6, i32 0, i32 3
  %8 = load %String* (%Object*)*, %String* (%Object*)** %7
  %9 = call %String* %8(%Object* %4)
  %10 = call i8* @String_getData(%String* %9)
  %11 = call i32 (...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @1, i32 0, i32 0), i8* %10)
  %12 = load %BinNode*, %BinNode** %1, align 8
  %13 = getelementptr inbounds %BinNode, %BinNode* %12, i32 0, i32 2
  %14 = load %Node*, %Node** %13
  %15 = getelementptr inbounds %Node, %Node* %14, i32 0, i32 0
  %16 = load %Node_vtable*, %Node_vtable** %15
  %17 = getelementptr inbounds %Node_vtable, %Node_vtable* %16, i32 0, i32 5
  %18 = load %Nothing* (%Node*)*, %Nothing* (%Node*)** %17
  %19 = call %Nothing* %18(%Node* %14)
  %20 = load %BinNode*, %BinNode** %1, align 8
  %21 = getelementptr inbounds %BinNode, %BinNode* %20, i32 0, i32 3
  %22 = load %Node*, %Node** %21
  %23 = getelementptr inbounds %Node, %Node* %22, i32 0, i32 0
  %24 = load %Node_vtable*, %Node_vtable** %23
  %25 = getelementptr inbounds %Node_vtable, %Node_vtable* %24, i32 0, i32 5
  %26 = load %Nothing* (%Node*)*, %Nothing* (%Node*)** %25
  %27 = call %Nothing* %26(%Node* %22)
  %28 = call %Nothing* @Nothing_create()
  ret %Nothing* %28
}

define dso_local i64 @main() {
main:
  %0 = call %String* @String_create(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @2, i32 0, i32 0))
  %1 = call %String* @String_create(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @3, i32 0, i32 0))
  %2 = call %LeafNode* @LeafNode_create(%String* %1)
  %3 = call %String* @String_create(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @4, i32 0, i32 0))
  %4 = call %LeafNode* @LeafNode_create(%String* %3)
  %5 = call %BinNode* @BinNode_create(%String* %0, %LeafNode* %2, %LeafNode* %4)
  %6 = alloca %BinNode*, align 8
  store %BinNode* %5, %BinNode** %6, align 8
  %7 = load %BinNode*, %BinNode** %6, align 8
  %8 = getelementptr inbounds %BinNode, %BinNode* %7, i32 0, i32 0
  %9 = load %BinNode_vtable*, %BinNode_vtable** %8
  %10 = getelementptr inbounds %BinNode_vtable, %BinNode_vtable* %9, i32 0, i32 5
  %11 = load %Nothing* (%BinNode*)*, %Nothing* (%BinNode*)** %10
  %12 = call %Nothing* %11(%BinNode* %7)
  ret i64 0
}
