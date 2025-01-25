The following notes come from the YouTube playlist: [Introduction to Rasa](https://www.youtube.com/watch?v=Ap62n_YAVZ8&list=PL75e0qA87dlErcimrWHKEUq4b-x9PrpLe)
### Introduction to Rasa

Rasa is designed to help a task oriented dialogue system. This means the user wants to do something specific through talking to an automated system in a two-way conversation. **Task Oriented Dialogue System**.

Rasa is **a framework that makes it easier to build custom chatbots.**
The core of building a Rasa assistant is providing examples that your system can learn from. 

Rasa combines the history of NLP such as rule-based text and transformer-based text (neural methods).

#### Key Points:
- NLU (Natural Language Understanding): Raw text in, machine-readable information out
- Methods to do NLU:
	- Rule-based approach: cannot handle things it has not seen before
	- Neural approach: requires training examples (makes _informed guesses_)
- A Rasa assistant can use both methods.
- Dialog Policy: Given the conversation so far, what should your assistant say/do?
	- Rule-based Policy: A dialog tree of all possible paths a conversation can take. It cannot handle actual conversations with digressions and other inputs.
	- Neural Policy: This allows for a more natural conversation.
- It is recommended to use both policies.
- How do conversations work and improve over time? "Conversation-driven development" or manually reviewing and annotating conversations.

### Creating a New Assistant

Rasa is installed through pip and initialized in the command line interpreter (CLI). It already has a basic initial model easily initialized and ran. 

#### Key Points:
- Minimum files needed:
	- Domain file: shows everything the assistant knows about.
	- Config file: sets out our NLU pipeline.
	- At least 1 data file: by default, there are 3 data files: stories, rules, NLU.
		- NLU: different examples of how people can describe intent
		- Stories: potential conversation flow
		- Rules: to find conditional rules.

```python
1. rasa -h 
2. rasa train # trains a new model and stores it in the model directory
3. rasa shell # allows you to talk to the assistant inside the shell
4. rasa shell --debug # provides more information to be able to debug
```

### The Domain File (Intents & Responses)

The domain file is the most important file in Rasa. The domain file is a directory of everything that your assistant 'knows'.

#### Key Points:
- In the domain file, there are:
	- Responses: what the assistant will reply.
	- Intents: categories of things user can say that will warrant a response.
	- Slots: variables remembered over the course of the conversation.
	- Entities: pieces of information extracted from raw input text.
	- Forms and Actions: these add application logic and extend what the assistant can do.
- Assistant has rigid replies unless we have Natural Language Generation (NLG).
- Slots are e.g. {name}
- Responses can be button/images. They have to be specifically designed and formatted in CSS.
- Intents are what the users say to the assistant.
- **Pro-Tip:** Start with the fewest intents possible.

### Training Data and Rules

In the context of a Rasa project, there are multiple different types of data:
- Text data used to pretrain any models or features we are using
- User-generated text
- Patterns of conversation

#### Key Points
- Giving examples of where we can find data for training:
	- Customer support logs
	- User conversations with your assistant (__best choice__)
- Stories, rules, determine how conversations should go.
- Intents, determine how users say things.
- Default guidelines use the TED policy to guess what to reply if it does not follow the stories.
- If the reply does not meet a certain confidence threshold, reply with a fallback.
- If generating your own conversational patterns, (initially)
	- start with common flows, "happy paths"
	- add common errors/digressions
- In stories, there is a feature "**feedback**". 
- Rules describe short pieces of conversation that always go the same way.
- Intents are determined and saved in NLU file.
- Give users an escape hatch right away. (in and out of scope intent)
- Do not use intents for saving information, use _entities or slots_ instead.
- If the utterance(user text) is ambiguous, use end-to-end instead (the raw text as training data without classifying it)


**Important Points**
- Have small stories that aren't full conversations. They will be later combined.
- Use rules for one-off interactions. Do not use rules for multi-turn interactions.
- Do not use OR statements and checkpointing often
- Do not write out every possible conversation flow start to finish
- ASAP do user testing
- Use modified content analysis:
	- Go through data by hand and assign each data point to a group
	- If no existing group fits, add a new one.
	- At given intervals, go through your groups and combine or separate them as needed.
	- Start with 2-3 passes through your dataset.

### Entities

Entities are structured pieces of information inside of a user message. It can be any important detail that your assistant could use later in a conversation (memory).

#### Key points
- Training data for entity extraction should be include in the NLU.yml file.
- Three _methods_ for entity extraction
	- Using pre-built models (_Duckling, SpaCy_). The models have to be referenced in order to be used.
	- Using _Regex_, for entities that match a specific pattern. For entities that follow a deterministic pattern. Do not forget to name the entity the same as the Regex pattern.
	- Using _Machine Learning_, you will need training data for better results. Rasa comes with a few machine learning models (Rasa's DIETClassifier).
- The output of the entity extraction is a snippet of JSON which contains the details of: entity category, entity value, confidence levels, the component that extracted the entity.
- _Synonyms_ can be used to map the extracted values to a single standardized value. We want extracted entity values to be normalized and mapped to a single value.
- Two _methods_ of adding synonyms to Rasa
	- Adding a new section "synonym" to the nlu.yml, you have to define the synonym and provide examples of how it may be referred to. 
	- Adding the synonyms in line to your NLU training examples. You add an extra parameter "value" that will reference the value that extracted entities will have to be mapped to.
- Synonym mapping happens after entity extraction happens. This means that you will need training data to extract entities first.
- _Lookup tables_ are lists of words used to generate case-sensitive regular expression patterns.
- _Entity roles and groups_ allow you to add more details to your entities.
- _Entity roles_ allow you to define the roles of the entities of the same groups. (origin, destination)
- _Entity groups_ allow you to put extracted entities under a specific group.
- Entity roles can also be configured to influence the conversation flow.

### Slots

Slots are the assistant's memory. They enable your assistant to store important details and later use them in a specific context. Slots are defined in the domain.yml file. We have to add the slot name, slot type, a parameter that determines whether or not the slot should influence the conversation flow, and mappings.

#### Key points
- Two methods of setting slots
	- Using _NLU_, depending on how we configure the slot mappings.
	- Using _custom actions_ (expanded upon later)
- Slots can be configured to influence the flow of the conversation. It has a configuration flag when setting up the slot.
- Depending on the type of slot, the flow can be influenced by the value of the slot or whether the value of this slot is present.
- A general rule of thumb is to configure the slots to not influence if you do not have a specific reason of why a specific slot should have an influence on how a dialogue management model works.
- If the slots are configured to influence the flow of the conversation, you have to include them in your training stories.
- _OR Slot values_ allow you to define lots of different situation where different slots will be set by writing less stories.
- _Slot mappings_ allow you to define how each slot will be filled in. Slot mappings are applied after each user message. They are applied after each user message as the conversation goes.
- _from_entity slot mapping_ fills in the slots based on the extracted entities. Fill in the slots from the entities basically. You can also add role and group constraints. We can also define intent and not_intent.
- _from_text slot mapping_ allows you to use the text of the latest user message to fill in the slot with additional parameters such as intent.
- _from_intent slot mapping_ is based on the predicted intents. The slot will be filled in with a predetermined value if an intent is predicted.
- _from_trigger_intent slot mapping_ will fill a slot with a specific defined value if a form is activated by a user message with a specific intent.
- _custom slot mapping_ if none of the predefined slot mapping fit the use case. This happens using slot validation actions.
- _Slot type: text_ can be used to store any text information. It can influence the conversation based on whether or not the slot has been set.
- _Slot type: Boolean_ used to store information that can get the values true or false, e.g. user authentication from user ID.
- _Slot type: categorical_ used to store values that can get one of the possible N values.
- _Slot type: float_ used to store numerical values.
- _Slot type: list_ used to store a list of values. When configured, only the presence of the slot can have influence on the flow of the conversation.
- _Slot type: any_ used to store any arbitrary values. Slots of this type do not have any influence on the conversation flow.
- _Additional Configuration: initial_value_ sets a default initial vale to your slot by configuring the parameter.