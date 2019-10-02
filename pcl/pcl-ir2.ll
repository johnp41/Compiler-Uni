; ModuleID = 'tomodulo'
source_filename = "tomodulo"
target triple = "x86_64-pc-linux-gnu"

%struct.main_ = type { %dummy*, [4 x i8], i8* }
%dummy = type opaque

declare void @writeInteger(i16)

declare void @writeChar(i8)

declare void @writeBoolean(i1)

declare void @writeString(i8*)

declare void @writeReal(x86_fp80)

declare i16 @readInteger()

declare i1 @readBoolean()

declare i8 @readChar()

declare void @readString(i16, i8*)

declare x86_fp80 @readReal()

declare i16 @abs(i16)

declare x86_fp80 @fabs(x86_fp80)

declare x86_fp80 @sqrt(x86_fp80)

declare x86_fp80 @sin(x86_fp80)

declare x86_fp80 @cos(x86_fp80)

declare x86_fp80 @tan(x86_fp80)

declare x86_fp80 @arctan(x86_fp80)

declare x86_fp80 @exp(x86_fp80)

declare x86_fp80 @ln(x86_fp80)

declare x86_fp80 @phi()

declare i16 @trunc(x86_fp80)

declare i16 @round(x86_fp80)

declare i16 @ord(i8)

declare i8 @chr(i16)

define i32 @main() {
entry:
  %0 = alloca %struct.main_
  %1 = getelementptr %struct.main_, %struct.main_* %0, i32 0, i32 1
  %2 = getelementptr inbounds [4 x i8], [4 x i8]* %1, i32 0, i32 0
  %3 = alloca i8*
  store i8* %2, i8** %3
  %4 = alloca [4 x i8]
  %5 = getelementptr [4 x i8], [4 x i8]* %4, i32 0, i32 0
  store i8 97, i8* %5
  %6 = getelementptr [4 x i8], [4 x i8]* %4, i32 0, i32 1
  store i8 98, i8* %6
  %7 = getelementptr [4 x i8], [4 x i8]* %4, i32 0, i32 2
  store i8 99, i8* %7
  %8 = getelementptr [4 x i8], [4 x i8]* %4, i32 0, i32 3
  store i8 0, i8* %8
  %9 = getelementptr inbounds [4 x i8], [4 x i8]* %4, i32 0, i32 0
  %10 = alloca i8*
  store i8* %9, i8** %10
  %11 = load i8*, i8** %10
  store i8* %11, i8** %3
  %12 = getelementptr %struct.main_, %struct.main_* %0, i32 0, i32 1
  %13 = getelementptr inbounds [4 x i8], [4 x i8]* %12, i32 0, i32 0
  %14 = alloca i8*
  store i8* %13, i8** %14
  %15 = load i8*, i8** %14
  call void @writeString(i8* %15)
  ret i32 40
}
