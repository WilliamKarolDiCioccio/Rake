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