#include "MyProject.h"
#include "SortArrayBPFunctionLibrary.h"

struct FArraySortByFieldPredicate
{
	FArraySortByFieldPredicate(const FString &InFieldName, ESortDirection InSortDirection)
		: FieldName(InFieldName), SortDirection(InSortDirection)
	{
	}

	bool operator ()(const AActor& A, const AActor& B) const
	{
		UClass *ourClass = A.GetClass();
		if (ourClass != B.GetClass())
			return false;

		UProperty *targetProperty = FindField<UProperty>(ourClass, *FieldName);
		if (targetProperty == nullptr)
			return false;

		const void *Aa = (SortDirection == ESortDirection::ASCENDING) ? &A : &B;
		const void *Bb = (SortDirection == ESortDirection::ASCENDING) ? &B : &A;

		if (targetProperty->IsA<UByteProperty>())
		{
			return Cast<UByteProperty>(targetProperty)->GetPropertyValue_InContainer(Aa) <
				Cast<UByteProperty>(targetProperty)->GetPropertyValue_InContainer(Bb);
		}
		else if (targetProperty->IsA<UIntProperty>())
		{
			return
				Cast<UIntProperty>(targetProperty)->GetPropertyValue_InContainer(Aa) <
				Cast<UIntProperty>(targetProperty)->GetPropertyValue_InContainer(Bb);
		}
		else if (targetProperty->IsA<UUInt32Property>())
		{
			return
				Cast<UUInt32Property>(targetProperty)->GetPropertyValue_InContainer(Aa) <
				Cast<UUInt32Property>(targetProperty)->GetPropertyValue_InContainer(Bb);
		}
		else if (targetProperty->IsA<UFloatProperty>())
		{
			return
				Cast<UFloatProperty>(targetProperty)->GetPropertyValue_InContainer(Aa) <
				Cast<UFloatProperty>(targetProperty)->GetPropertyValue_InContainer(Bb);
		}
		else if (targetProperty->IsA<UDoubleProperty>())
		{
			return
				Cast<UDoubleProperty>(targetProperty)->GetPropertyValue_InContainer(Aa) <
				Cast<UDoubleProperty>(targetProperty)->GetPropertyValue_InContainer(Bb);
		}
		else if (targetProperty->IsA<UStrProperty>())
		{
			return
				Cast<UStrProperty>(targetProperty)->GetPropertyValue_InContainer(Aa) <
				Cast<UStrProperty>(targetProperty)->GetPropertyValue_InContainer(Bb);
		}
		else if (targetProperty->IsA<UNameProperty>())
		{
			return
				Cast<UNameProperty>(targetProperty)->GetPropertyValue_InContainer(Aa) <
				Cast<UNameProperty>(targetProperty)->GetPropertyValue_InContainer(Bb);
		}
		else if (targetProperty->IsA<UTextProperty>())
		{
			return
				Cast<UTextProperty>(targetProperty)->GetPropertyValue_InContainer(Aa).ToString() <
				Cast<UTextProperty>(targetProperty)->GetPropertyValue_InContainer(Bb).ToString();
		}
		// fall back, just let diff type win:
		else
			return false;
	}

	FString FieldName;
	ESortDirection SortDirection;
};

//USortArrayBPFunctionLibrary::USortArrayBPFunctionLibrary(const class FObjectInitializer& PCIP)
//	: Super(PCIP)
//{
//
//}


void USortArrayBPFunctionLibrary::Array_Sort(const TArray<int32>& TargetArray, const UArrayProperty* ArrayProp, const FString &FieldName, ESortDirection SortDirection)
{
	// We should never hit these!  They're stubs to avoid NoExport on the class.  Call the Generic* equivalent instead
	check(0);
}

void USortArrayBPFunctionLibrary::GenericArray_Sort(void* TargetArray, const UArrayProperty* ArrayProp, const FString &FieldName, ESortDirection SortDirection)
{
	if (TargetArray)
	{
		TArray<AActor *> *actorArray = (TArray<AActor *> *)TargetArray;
		if (actorArray != nullptr)
		{
			actorArray->Sort(FArraySortByFieldPredicate(FieldName, SortDirection));
		}
	}
}