#include "plugin.hpp"

struct Nova : Module
{
	enum ParamIds
	{
		START_PARAM,
		RESET_PARAM,
		DIRECTION_PARAM,
		RECORD_PARAM,
		ENUMS(GAINS_PARAM, 8),
		ENUMS(MUTES_PARAM, 8),
		ENUMS(SKIPS_PARAM, 8),
		ENUMS(REVERSES_PARAM, 8),
		ENUMS(TRIGGERS_PARAM, 8),
		ATTACK_PARAM,
		RELEASE_PARAM,
		PITCH_PARAM,
		NUM_PARAMS
	};
	enum InputIds
	{
		IN_INPUT,
		CLOCK_INPUT,
		START_INPUT,
		RESET_INPUT,
		DIRECTION_INPUT,
		RECORD_INPUT,
		ENUMS(TRIGGERS_INPUT, 8),

		NUM_INPUTS
	};
	enum OutputIds
	{
		ENUMS(OUTS_OUTPUT, 8),
		MAINOUT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds
	{
		ENUMS(SEQS_LIGHT, 8),
		NUM_LIGHTS
	};

	Nova()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(START_PARAM, 0.f, 1.f, 0.f, "Sequencer Start");
		configParam(RESET_PARAM, 0.f, 1.f, 0.f, "Sequencer Reset");
		configParam(DIRECTION_PARAM, 0.f, 1.f, 0.f, "Sequencer Direction");
		configParam(RECORD_PARAM, 0.f, 1.f, 0.f, "Sampler Record Start");

		for (int i = 0; i < 8; ++i)
		{
			configParam(GAINS_PARAM + i, 0.f, 1.f, 1.f, string::f("Sample %d Gain", i + 1), "dB", -10.f, 20.f);
			configParam(MUTES_PARAM + i, 0.f, 1.f, 0.f, string::f("Sample %d Mute", i + 1));
			configParam(SKIPS_PARAM + i, 0.f, 1.f, 0.f, string::f("Sample %d Skip", i + 1));
			configParam(REVERSES_PARAM + i, 0.f, 1.f, 0.f, string::f("Sample %d Reverse", i + 1));
			configParam(TRIGGERS_PARAM + i, 0.f, 1.f, 0.f, string::f("Sample %d Trigger", i + 1));
		}

		configParam(ATTACK_PARAM, 0.f, 1.f, 0.f, "Global Sample Attack");
		configParam(RELEASE_PARAM, 0.f, 1.f, 0.f, "Global Sample Release");
		configParam(PITCH_PARAM, 0.f, 1.f, 0.5f, "Global Sample Pitch");
	}

	void process(const ProcessArgs &args) override
	{
	}
};

struct NovaWidget : ModuleWidget
{
	NovaWidget(Nova *module)
	{
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Nova.svg")));

		addChild(createWidget<FFHexScrew>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<FFHexScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<FFHexScrew>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<FFHexScrew>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<FFDPW>(mm2px(Vec(28.976, 59.34)), module, Nova::START_PARAM));
		addParam(createParamCentered<FFDPW>(mm2px(Vec(28.976, 77.302)), module, Nova::RESET_PARAM));
		addParam(createParamCentered<FFDPW>(mm2px(Vec(28.976, 95.263)), module, Nova::DIRECTION_PARAM));
		addParam(createParamCentered<FFDPW>(mm2px(Vec(28.976, 113.225)), module, Nova::RECORD_PARAM));

		addParam(createParamCentered<FF15GKnob>(mm2px(Vec(190.051, 39.694)), module, Nova::ATTACK_PARAM));
		addParam(createParamCentered<FF15GKnob>(mm2px(Vec(190.051, 65.493)), module, Nova::RELEASE_PARAM));
		addParam(createParamCentered<FF15GKnob>(mm2px(Vec(190.051, 91.272)), module, Nova::PITCH_PARAM));

		addInput(createInputCentered<FF01JKPort>(mm2px(Vec(22.88, 23.417)), module, Nova::IN_INPUT));
		addInput(createInputCentered<FF01JKPort>(mm2px(Vec(22.88, 41.379)), module, Nova::CLOCK_INPUT));
		addInput(createInputCentered<FF01JKPort>(mm2px(Vec(16.335, 59.34)), module, Nova::START_INPUT));
		addInput(createInputCentered<FF01JKPort>(mm2px(Vec(16.335, 77.302)), module, Nova::RESET_INPUT));
		addInput(createInputCentered<FF01JKPort>(mm2px(Vec(16.335, 95.263)), module, Nova::DIRECTION_INPUT));
		addInput(createInputCentered<FF01JKPort>(mm2px(Vec(16.335, 113.225)), module, Nova::RECORD_INPUT));

		addOutput(createOutputCentered<FF01JKPort>(mm2px(Vec(190.051, 110.766)), module, Nova::MAINOUT_OUTPUT));

		for (int i = 0; i < 8; ++i)
		{
			float deltaX = 15.05f;
			addParam(createParamCentered<FF10GKnob>(mm2px(Vec(61.531 + (i * deltaX), 23.43)), module, Nova::GAINS_PARAM + i));
			addParam(createParamCentered<FFDPW>(mm2px(Vec(61.531 + (i * deltaX), 38.834)), module, Nova::MUTES_PARAM + i));
			addParam(createParamCentered<FFDPW>(mm2px(Vec(61.531 + (i * deltaX), 54.238)), module, Nova::SKIPS_PARAM + i));
			addParam(createParamCentered<FFDPW>(mm2px(Vec(61.531 + (i * deltaX), 69.642)), module, Nova::REVERSES_PARAM + i));
			addParam(createParamCentered<FFDPW>(mm2px(Vec(61.531 + (i * deltaX), 85.046)), module, Nova::TRIGGERS_PARAM + i));
			addInput(createInputCentered<FF01JKPort>(mm2px(Vec(61.531 + (i * deltaX), 97.487)), module, Nova::TRIGGERS_INPUT + i));
			addOutput(createOutputCentered<FF01JKPort>(mm2px(Vec(61.531 + (i * deltaX), 110.766)), module, Nova::OUTS_OUTPUT + i));
			addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(61.531 + (i * deltaX), 117.503)), module, Nova::SEQS_LIGHT + i));
		}
	}
};

Model *modelNova = createModel<Nova, NovaWidget>("Nova");