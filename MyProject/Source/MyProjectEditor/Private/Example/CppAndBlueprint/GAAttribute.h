/**
 * @brief https://wiki.unrealengine.com/How_To_Create_Custom_Blueprint_Pin
 First you will need Editor module in your plugin/game project. You can find information how to add it here:

 https://answers.unrealengine.com/questions/41509/extending-editor-engine.html
 */

USTRUCT(BlueprintType)
struct FGAAttribute
{
	GENERATED_USTRUCT_BODY()
public:
	//It's important to mark property as UPROPERTY(), it doesn't need to have any specifiers though.
	UPROPERTY(BlueprintReadOnly)
		FName AttributeName;
};