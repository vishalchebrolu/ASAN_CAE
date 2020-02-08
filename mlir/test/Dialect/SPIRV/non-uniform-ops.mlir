// RUN: mlir-opt -split-input-file -verify-diagnostics %s | FileCheck %s

//===----------------------------------------------------------------------===//
// spv.GroupNonUniformBallot
//===----------------------------------------------------------------------===//

func @group_non_uniform_ballot(%predicate: i1) -> vector<4xi32> {
  // CHECK: %{{.*}} = spv.GroupNonUniformBallot "Workgroup" %{{.*}}: vector<4xi32>
  %0 = spv.GroupNonUniformBallot "Workgroup" %predicate : vector<4xi32>
  return %0: vector<4xi32>
}

// -----

func @group_non_uniform_ballot(%predicate: i1) -> vector<4xi32> {
  // expected-error @+1 {{execution scope must be 'Workgroup' or 'Subgroup'}}
  %0 = spv.GroupNonUniformBallot "Device" %predicate : vector<4xi32>
  return %0: vector<4xi32>
}

// -----

//===----------------------------------------------------------------------===//
// spv.GroupNonUniformElect
//===----------------------------------------------------------------------===//

// CHECK-LABEL: @group_non_uniform_elect
func @group_non_uniform_elect() -> i1 {
  // CHECK: %{{.+}} = spv.GroupNonUniformElect "Workgroup" : i1
  %0 = spv.GroupNonUniformElect "Workgroup" : i1
  return %0: i1
}

// -----

func @group_non_uniform_elect() -> i1 {
  // expected-error @+1 {{execution scope must be 'Workgroup' or 'Subgroup'}}
  %0 = spv.GroupNonUniformElect "CrossDevice" : i1
  return %0: i1
}

// -----

//===----------------------------------------------------------------------===//
// spv.GroupNonUniformIAdd
//===----------------------------------------------------------------------===//

// CHECK-LABEL: @group_non_uniform_iadd_reduce
func @group_non_uniform_iadd_reduce(%val: i32) -> i32 {
  // CHECK: %{{.+}} = spv.GroupNonUniformIAdd "Workgroup" "Reduce" %{{.+}} : i32
  %0 = spv.GroupNonUniformIAdd "Workgroup" "Reduce" %val : i32
  return %0: i32
}

// CHECK-LABEL: @group_non_uniform_iadd_clustered_reduce
func @group_non_uniform_iadd_clustered_reduce(%val: vector<2xi32>) -> vector<2xi32> {
  %four = spv.constant 4 : i32
  // CHECK: %{{.+}} = spv.GroupNonUniformIAdd "Workgroup" "ClusteredReduce" %{{.+}} cluster_size(%{{.+}}) : vector<2xi32>
  %0 = spv.GroupNonUniformIAdd "Workgroup" "ClusteredReduce" %val cluster_size(%four) : vector<2xi32>
  return %0: vector<2xi32>
}

// -----

func @group_non_uniform_iadd_reduce(%val: i32) -> i32 {
  // expected-error @+1 {{execution scope must be 'Workgroup' or 'Subgroup'}}
  %0 = spv.GroupNonUniformIAdd "Device" "Reduce" %val : i32
  return %0: i32
}

// -----

func @group_non_uniform_iadd_clustered_reduce(%val: vector<2xi32>) -> vector<2xi32> {
  // expected-error @+1 {{cluster size operand must be provided for 'ClusteredReduce' group operation}}
  %0 = spv.GroupNonUniformIAdd "Workgroup" "ClusteredReduce" %val : vector<2xi32>
  return %0: vector<2xi32>
}

// -----

func @group_non_uniform_iadd_clustered_reduce(%val: vector<2xi32>, %size: i32) -> vector<2xi32> {
  // expected-error @+1 {{cluster size operand must come from a constant op}}
  %0 = spv.GroupNonUniformIAdd "Workgroup" "ClusteredReduce" %val cluster_size(%size) : vector<2xi32>
  return %0: vector<2xi32>
}

// -----

func @group_non_uniform_iadd_clustered_reduce(%val: vector<2xi32>) -> vector<2xi32> {
  %five = spv.constant 5 : i32
  // expected-error @+1 {{cluster size operand must be a power of two}}
  %0 = spv.GroupNonUniformIAdd "Workgroup" "ClusteredReduce" %val cluster_size(%five) : vector<2xi32>
  return %0: vector<2xi32>
}