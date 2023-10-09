modded class PluginRecipesManagerBase extends PluginBase
{
	override void RegisterRecipies()
	{
		super.RegisterRecipies();

		RegisterRecipe(new OpenCanStoneRecipe);
		
	}
};