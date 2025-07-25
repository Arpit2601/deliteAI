/*
 * SPDX-FileCopyrightText: (C) 2025 DeliteAI Authors
 *
 * SPDX-License-Identifier: Apache-2.0
 */

import org.gradle.api.plugins.ExtraPropertiesExtension

class NEGradleConfig(extra: ExtraPropertiesExtension) {
    val commonCmakeArguments: List<String> = extra.get("cmakeArgumentsCommon").toString().split(" ")
    val androidCmakeArguments: List<String> = extra.get("cmakeArgumentsAndroid").toString().split(" ")

    val releaseVersion: String = extra.get("sdkReleaseVersion").toString()
    val ndkVersion: String = extra.get("ndkVersion").toString()

    val compileSdk = 35
    val targetSdk = 35
    val minSdk = 31 // Update minSdk to 31 if Gemini needs to be enabled

    val geminiEnabled: Boolean = androidCmakeArguments.any { it == "-DGEMINI=1" }
}
