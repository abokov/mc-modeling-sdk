package org.vamp_plugins;

public class test
{
    public static void main(String[] args) {

        // This is the name of a Vamp plugin we know we have installed
        String key = "vamp-example-plugins:percussiononsets";

        PluginLoader loader = PluginLoader.getInstance();

        try {
            Plugin p = loader.loadPlugin(key, 44100);
            System.out.println("identifier: " + p.getIdentifier());
            System.out.println("name: " + p.getName());
            System.out.println("description: " + p.getDescription());
            System.out.println("version: " + p.getPluginVersion());
        } catch (PluginLoader.LoadFailedException e) {
            System.out.println("Plugin load failed");
        }
    }
}
