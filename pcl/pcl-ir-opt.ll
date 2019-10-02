; ModuleID = 'pcl-ir.ll'
source_filename = "tomodulo"
target triple = "x86_64-pc-linux-gnu"

%struct.main_ = type { %struct.main_*, i16, x86_fp80 }

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

declare x86_fp80 @pi()

declare i16 @trunc(x86_fp80)

declare i16 @round(x86_fp80)

declare i16 @ord(i8)

declare i8 @chr(i16)

define i32 @main() {
entry:
  %0 = alloca %struct.main_
  %1 = getelementptr %struct.main_, %struct.main_* %0, i32 0, i32 0
  store %struct.main_* %0, %struct.main_** %1
  %2 = alloca [55 x i8]
  %3 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 0
  store i8 71, i8* %3
  %4 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 1
  store i8 105, i8* %4
  %5 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 2
  store i8 118, i8* %5
  %6 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 3
  store i8 101, i8* %6
  %7 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 4
  store i8 32, i8* %7
  %8 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 5
  store i8 109, i8* %8
  %9 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 6
  store i8 101, i8* %9
  %10 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 7
  store i8 32, i8* %10
  %11 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 8
  store i8 97, i8* %11
  %12 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 9
  store i8 110, i8* %12
  %13 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 10
  store i8 32, i8* %13
  %14 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 11
  store i8 105, i8* %14
  %15 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 12
  store i8 110, i8* %15
  %16 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 13
  store i8 116, i8* %16
  %17 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 14
  store i8 32, i8* %17
  %18 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 15
  store i8 97, i8* %18
  %19 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 16
  store i8 110, i8* %19
  %20 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 17
  store i8 100, i8* %20
  %21 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 18
  store i8 32, i8* %21
  %22 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 19
  store i8 105, i8* %22
  %23 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 20
  store i8 32, i8* %23
  %24 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 21
  store i8 97, i8* %24
  %25 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 22
  store i8 109, i8* %25
  %26 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 23
  store i8 32, i8* %26
  %27 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 24
  store i8 103, i8* %27
  %28 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 25
  store i8 111, i8* %28
  %29 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 26
  store i8 110, i8* %29
  %30 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 27
  store i8 110, i8* %30
  %31 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 28
  store i8 97, i8* %31
  %32 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 29
  store i8 32, i8* %32
  %33 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 30
  store i8 112, i8* %33
  %34 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 31
  store i8 117, i8* %34
  %35 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 32
  store i8 116, i8* %35
  %36 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 33
  store i8 32, i8* %36
  %37 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 34
  store i8 105, i8* %37
  %38 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 35
  store i8 116, i8* %38
  %39 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 36
  store i8 32, i8* %39
  %40 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 37
  store i8 105, i8* %40
  %41 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 38
  store i8 110, i8* %41
  %42 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 39
  store i8 32, i8* %42
  %43 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 40
  store i8 97, i8* %43
  %44 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 41
  store i8 32, i8* %44
  %45 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 42
  store i8 114, i8* %45
  %46 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 43
  store i8 101, i8* %46
  %47 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 44
  store i8 97, i8* %47
  %48 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 45
  store i8 108, i8* %48
  %49 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 46
  store i8 32, i8* %49
  %50 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 47
  store i8 45, i8* %50
  %51 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 48
  store i8 118, i8* %51
  %52 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 49
  store i8 97, i8* %52
  %53 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 50
  store i8 114, i8* %53
  %54 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 51
  store i8 32, i8* %54
  %55 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 52
  store i8 10, i8* %55
  %56 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 53
  store i8 32, i8* %56
  %57 = getelementptr [55 x i8], [55 x i8]* %2, i32 0, i32 54
  store i8 0, i8* %57
  %58 = getelementptr inbounds [55 x i8], [55 x i8]* %2, i32 0, i32 0
  call void @writeString(i8* %58)
  %59 = getelementptr %struct.main_, %struct.main_* %0, i32 0, i32 2
  %60 = call i16 @readInteger()
  %61 = sitofp i16 %60 to x86_fp80
  store x86_fp80 %61, x86_fp80* %59
  %62 = alloca [27 x i8]
  %63 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 0
  store i8 116, i8* %63
  %64 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 1
  store i8 104, i8* %64
  %65 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 2
  store i8 101, i8* %65
  %66 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 3
  store i8 32, i8* %66
  %67 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 4
  store i8 114, i8* %67
  %68 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 5
  store i8 101, i8* %68
  %69 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 6
  store i8 97, i8* %69
  %70 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 7
  store i8 108, i8* %70
  %71 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 8
  store i8 32, i8* %71
  %72 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 9
  store i8 121, i8* %72
  %73 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 10
  store i8 111, i8* %73
  %74 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 11
  store i8 117, i8* %74
  %75 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 12
  store i8 32, i8* %75
  %76 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 13
  store i8 103, i8* %76
  %77 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 14
  store i8 97, i8* %77
  %78 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 15
  store i8 118, i8* %78
  %79 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 16
  store i8 101, i8* %79
  %80 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 17
  store i8 32, i8* %80
  %81 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 18
  store i8 105, i8* %81
  %82 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 19
  store i8 115, i8* %82
  %83 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 20
  store i8 32, i8* %83
  %84 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 21
  store i8 46, i8* %84
  %85 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 22
  store i8 46, i8* %85
  %86 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 23
  store i8 46, i8* %86
  %87 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 24
  store i8 46, i8* %87
  %88 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 25
  store i8 32, i8* %88
  %89 = getelementptr [27 x i8], [27 x i8]* %62, i32 0, i32 26
  store i8 0, i8* %89
  %90 = getelementptr inbounds [27 x i8], [27 x i8]* %62, i32 0, i32 0
  call void @writeString(i8* %90)
  %91 = getelementptr %struct.main_, %struct.main_* %0, i32 0, i32 2
  %92 = load x86_fp80, x86_fp80* %91
  call void @writeReal(x86_fp80 %92)
  %93 = alloca [2 x i8]
  %94 = getelementptr [2 x i8], [2 x i8]* %93, i32 0, i32 0
  store i8 10, i8* %94
  %95 = getelementptr [2 x i8], [2 x i8]* %93, i32 0, i32 1
  store i8 0, i8* %95
  %96 = getelementptr inbounds [2 x i8], [2 x i8]* %93, i32 0, i32 0
  call void @writeString(i8* %96)
  ret i32 0
}
