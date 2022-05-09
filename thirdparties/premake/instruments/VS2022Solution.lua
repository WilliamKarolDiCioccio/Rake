require('vstudio')

premake.api.register {
    name = "buildenabled",
    scope = "config",
    kind = "string",
    allowed {
        "Default",
        "Off",
        "On"
    }
}

premake.override(premake.vstudio.sln2005.elements, "projectConfigurationPlatforms", function(base, cfg, context)
    if context.prjCfg.buildenabled and context.prjCfg.buildenabled == "Off" then
        return {
            premake.vstudio.sln2005.activeCfg
        }
    else
        return base(cfg, context)
    end
end)